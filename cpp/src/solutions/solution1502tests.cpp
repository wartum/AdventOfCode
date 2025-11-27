#include <gtest/gtest.h>
#include "solutions.hpp"
#include "solution1502.hpp"

using namespace std;
using namespace solutions;
using namespace solutions::solution1502;

TEST(solution1502, create_box)
{
    Box box("12x10x2");
    EXPECT_EQ(box.length, 12);
    EXPECT_EQ(box.width, 10);
    EXPECT_EQ(box.height, 2);
    EXPECT_THROW(Box("12xasdx2"), InvalidInputException);
    EXPECT_THROW(Box("12x20"), InvalidInputException);
    EXPECT_THROW(Box("12x20x2x10"), InvalidInputException);
}

TEST(solution1502, print_box)
{
    Box box("12x10x2");
    stringstream s;
    s << box;
    EXPECT_EQ(s.str(), "[ 12x10x2 ]");
}

TEST(solution1502, wrapping_paper_area)
{
    Box box1(2,3,4);
    Box box2(1,1,10);
    EXPECT_EQ(box1.wrapping_paper_area(), 58);
    EXPECT_EQ(box2.wrapping_paper_area(), 43);
}
