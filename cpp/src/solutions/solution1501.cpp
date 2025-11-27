#include "solutions.hpp"

using namespace std;
using namespace solutions;

Solution solutions::solution1501::solve(const string &input)
{
    int current_floor = 0, i = 1;
    optional<int> first_basement_position = {};
    for (char c : input)
    {
        if (c == '(')
            current_floor += 1;
        else if (c == ')')
            current_floor -= 1;
        if (!first_basement_position.has_value() && current_floor == -1)
            first_basement_position = i;
        i += 1;
    }

    return {
        one_star: to_string(current_floor),
        two_star: first_basement_position.has_value() ? to_string(first_basement_position.value()) : optional<string>()
    };
}
