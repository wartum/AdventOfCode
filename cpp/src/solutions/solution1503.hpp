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
    bool operator==(const Position &pos1, const Position &pos2);

    int travel(const std::string &input, bool with_robo_santa);
}

namespace std
{
    template<>
    struct hash<solutions::solution1503::Position> {
        std::size_t operator()(const solutions::solution1503::Position& p) const noexcept {
            std::size_t h1 = std::hash<int>()(p.x);
            std::size_t h2 = std::hash<int>()(p.y);
            return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
        }
    };
}
