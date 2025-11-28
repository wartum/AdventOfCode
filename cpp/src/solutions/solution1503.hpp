#pragma once
#include <ostream>

namespace solutions::solution1503
{
    struct Position
    {
        int x;
        int y;
    };
    std::ostream& operator<<(std::ostream &os, Position &position);
    bool operator<(const Position &pos1, const Position &pos2);

    int travel(const std::string &input, bool with_robo_santa);
}
