#include <openssl/evp.h>
#include <memory>
#include <functional>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <limits.h>

#include "solutions.hpp"
#include "solution1504.hpp"

using namespace std;
using namespace solutions;
using namespace solutions::solution1504;

string solutions::solution1504::md5(const string& data)
{
    try
    {
        unsigned char digest[EVP_MAX_MD_SIZE];
        unsigned int digest_len = 0;
        unique_ptr<EVP_MD_CTX, function<void(EVP_MD_CTX*)>>
            ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);

        if (!ctx.get())
            throw runtime_error("EVP_MD_CTX_new failed");

        if (EVP_DigestInit_ex(ctx.get(), EVP_md5(), nullptr) != 1)
            throw runtime_error("EVP_DigestInit_ex failed");

        if (EVP_DigestUpdate(ctx.get(), data.data(), data.size()) != 1)
            throw runtime_error("EVP_DigestUpdate failed");

        if (EVP_DigestFinal_ex(ctx.get(), digest, &digest_len) != 1)
            throw runtime_error("EVP_DigestFinal_ex failed");

        stringstream ss;
        ss << hex << setfill('0');
        for (unsigned int i = 0; i < digest_len; i++)
            ss << setw(2) << static_cast<int>(digest[i]);

        return ss.str();
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << "\n";
        return {};
    }
}

Solution solutions::solution1504::solve(stringstream &input)
{
    string key;
    getline(input, key);
    int i = -1, j = -1;
    while(!check_number(key, ++i, "00000"));
    while(!check_number(key, ++j, "000000"));

    return
    {
        to_string(i),
        to_string(j),
    };
}

bool solutions::solution1504::check_number(const std::string &key, int number, const std::string &pattern)
{
    stringstream data;
    data << key << number;
    return md5(data.str()).find(pattern) == 0;
}
