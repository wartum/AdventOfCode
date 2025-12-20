#include <gtest/gtest.h>

#include "solution1506.hpp"

using namespace solutions::solution1506;
using namespace std;

TEST(solution1506, read_instruction)
{
    vector<tuple<string, Instruction>> test_values
    {
        { "turn on 0,0 through 999,999", { Action::ON, { 0, 0 }, { 999, 999} } },
        { "toggle 0,0 through 999,0", { Action::TOGGLE, { 0, 0 }, { 999, 0} } },
        { "turn off 499,499 through 500,500", { Action::OFF, { 499, 499 }, { 500, 500} } },
    };

    for (auto &val : test_values)
        ASSERT_EQ(read_instruction(get<0>(val)), get<1>(val));
}

TEST(solution1506, execute_instruction)
{
    vector<tuple<string, int>> test_values
    {
        { "turn on 3,3 through 6,3", 4 },
        { "turn on 0,0 through 2,2", 9 },
        { "turn on 0,0 through 999,999", 1000000 },
        { "toggle 0,0 through 999,0", 1000 },
        { "turn off 499,499 through 500,500", 0 }
    };

    Grid grid;
    for (auto &val : test_values)
    {
        grid.lights->fill(0);
        grid.execute(read_instruction(get<0>(val)));
        ASSERT_EQ(grid.count_turned_on(), get<1>(val));
    }
}