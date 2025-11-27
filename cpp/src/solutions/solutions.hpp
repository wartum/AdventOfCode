#pragma once
#include <ostream>
#include <string>
#include <optional>

namespace solutions
{
    struct Solution
    {
        std::optional<std::string> one_star;
        std::optional<std::string> two_star;
    };

    std::ostream& operator<<(std::ostream& os, Solution &solution);
    Solution solve(int year, int day, const std::string &input);

    namespace solution1501
    {
        Solution solve(const std::string &input);
    }
}
