#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <curl/curl.h>
#include "inputs.hpp"

using namespace std;

void save_local(int year, int day, const string &content);
optional<stringstream> get_local(int year, int day);
optional<stringstream> get_online(int year, int day);
size_t input_received(void *buffer, size_t size, size_t nmemb, void *userp);
size_t input_received_headers(char *buffer, size_t size, size_t nitems, void *userdata);

optional<stringstream> inputs::get_input(int year, int day, bool use_cache)
{
    if (use_cache)
    {
        optional<stringstream> local_input = get_local(year, day);
        if (local_input.has_value())
        {
            return local_input;
        }
    }

    optional<stringstream> online_input = get_online(year, day);
    if (online_input.has_value())
    {
        save_local(year, day, online_input.value().str());
        return online_input;
    }

    cerr << "No input found\n";
    return {};
}

optional<stringstream> get_local(int year, int day)
{
    stringstream file_name, file_buffer;
    file_name << "input" << year << day << ".txt";

    ifstream input(file_name.str());
    if (input.is_open())
    {
        file_buffer << input.rdbuf();
        input.close();
        return file_buffer;
    }
    else
    {
        return {};
    }
}

void save_local(int year, int day, const string &content)
{
    stringstream file_name;
    file_name << "input" << year << day << ".txt";
    ofstream file(file_name.str());
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}

optional<stringstream> get_online(int year, int day)
{
    char* session_value = std::getenv("AOC_SESSION");
    if (session_value == NULL || strlen(session_value) == 0 )
    {
        cerr << "No session token" << endl;
        return {};
    }

    stringstream input_buffer, url, cookie;
    int status_code;
    CURL* curl = curl_easy_init();
    url << "https://adventofcode.com/" << year << "/day/" << day << "/input";
    cookie << "session=" << session_value;

    curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.str().c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, input_received);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &input_buffer);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, input_received_headers);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &status_code);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (status_code == 200)
        return input_buffer;
    else
        return {};
}

size_t input_received(void *buffer, size_t size, size_t nmemb, void *userp)
{
    auto input_buffer = reinterpret_cast<stringstream*>(userp);
    string input((char*)buffer, nmemb);
    *input_buffer << input;
    return nmemb;
}

size_t input_received_headers(char *buffer, size_t size, size_t nitems, void *status_code)
{
    string header((char*)buffer, nitems);
    if (header.find("HTTP/") == 0)
    {
        *reinterpret_cast<int*>(status_code) = stoi(header.substr(7));
    }
    return nitems;
}
