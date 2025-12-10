#include <iostream>
#include <curl/curl.h>
#include "inputs.hpp"
#include "params.hpp"
#include "solutions/solutions.hpp"

using namespace std;
using solutions::solve;

struct Program
{
    Program();
    ~Program();

    static int main(int argc, char **argv);
};

int main(int argc, char **argv)
{
    Program program;
    Program::main(argc, argv);
}

// Initialization
Program::Program()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

// Cleanup
Program::~Program()
{
    curl_global_cleanup();
}

// Main
int Program::main(int argc, char **argv)
{
    auto parameters_opt = params::read_params(argc, argv);
    if (!parameters_opt.has_value())
        return 1;
    auto parameters = parameters_opt.value();

    auto input = inputs::get_input(parameters.year, parameters.day, parameters.use_cache);
    if (!input.has_value())
        return 1;

    auto solution = solve(parameters.year, parameters.day, input.value());
    cout << solution << "\n";
    return 0;
}
