#include<gtest/gtest.h>
#include "solution1504.hpp"

using namespace solutions::solution1504;

TEST(solution1504, check_number)
{
    ASSERT_EQ(check_number("abcdef", 609043, "00000"), true);
    ASSERT_EQ(check_number("pqrstuv", 1048970, "00000"), true);
}
