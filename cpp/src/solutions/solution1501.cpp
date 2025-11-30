#include "solutions.hpp"
#include <sstream>

using namespace std;
using namespace solutions;

Solution solutions::solution1501::solve(stringstream &input)
{
    string line;
    std::getline(input, line);
    int current_floor = 0, i = 1;
    optional<int> first_basement_position = {};
    for (char c : line)
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
        to_string(current_floor),
        first_basement_position.has_value() ? to_string(first_basement_position.value()) : optional<string>()
    };
}
