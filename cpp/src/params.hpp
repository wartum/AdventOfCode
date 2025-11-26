#pragma once
#include <ostream>
#include <optional>

namespace params
{
    struct Params
    {
        int year;
        int day;
        bool use_cache;
    };
    std::ostream& operator<< (std::ostream &os, Params &params);
    std::optional<Params> read_params(int argc, char **argv);
}

