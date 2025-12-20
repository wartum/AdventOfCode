#include <iostream>
#include <string>
#include "params.hpp"

using namespace std;
using namespace params;

ostream& params::operator<<(ostream &os, Params &params)
{
    os << "[ year: " << params.year
       << ", day: " << params.day
       << ", use_cache: " << params.use_cache
       << " ]";
    return os;
}

optional<Params> params::read_params(int argc, char **argv)
{
    Params params {
        .year = 0,
        .day = 0,
        .use_cache = true
    };
    int index = 1;

    while (index < argc)
    {
        string p(argv[index]);
        if (p == "--year" || p == "-y")
        {
            if (index == argc - 1)
            {
                cerr << "Year value not provided\n";
                return params;
            }
            params.year = stoi(argv[++index]);
        }
        else if (p == "--day" || p == "-d")
        {
            if (index == argc - 1)
            {
                cerr << "Day value not provided\n";
                return params;
            }
            params.day = stoi(argv[++index]);
        }
        else if (p == "--no-cache")
        {
            params.use_cache = false;
        }
        index += 1;
    }

    if (params.year == 0)
    {
        cerr << "Valid year is mandatory\n";
        return {};
    }
    if (params.day == 0)
    {
        cerr << "Valid day is mandatory\n";
        return {};
    }

    return params;
}
