#include <gtest/gtest.h>
#include "solution1503.hpp"

using namespace std;
using namespace solutions;
using namespace solutions::solution1503;

TEST(solution1503, print_position)
{
    Position pos(3,12);
    stringstream ss;
    ss << pos;
    ASSERT_EQ(ss.str(), "(3,12)");
}

TEST(solution1503, travel_santa)
{
    ASSERT_EQ(travel(">", false), 2);
    ASSERT_EQ(travel("^>v<", false), 4);
    ASSERT_EQ(travel("^v^v^v^v^v", false), 2);
}

TEST(solution1503, travel_santa_robot)
{
    ASSERT_EQ(travel("^v", true), 3);
    ASSERT_EQ(travel("^>v<", true), 3);
    ASSERT_EQ(travel("^v^v^v^v^v", true), 11);
}
