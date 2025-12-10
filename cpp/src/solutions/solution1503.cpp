#include <iostream>
#include <sstream>
#include <unordered_set>

#include "solutions.hpp"
#include "solution1503.hpp"

using namespace std;
using namespace solutions;
using namespace solutions::solution1503;

Solution solutions::solution1503::solve(stringstream &input)
{
    string line;
    if (!getline(input, line))
        return {};
    int visited_without_robo_santa = travel(line, false);
    int visited_with_robo_santa = travel(line, true);

    return {
        to_string(visited_without_robo_santa),
        to_string(visited_with_robo_santa),
    };
}

int solutions::solution1503::travel(const string &input, bool with_robo_santa)
{
    unordered_set<Position> visited;
    Position santa_pos {0,0};
    Position robot_pos {0,0};
    Position *pos = &santa_pos;
    visited.insert(*pos);
    for (char c : input)
    {
        switch (c)
        {
            case '^': pos->y += 1; break;
            case 'v': pos->y -= 1; break;
            case '<': pos->x -= 1; break;
            case '>': pos->x += 1; break;
        }
        visited.insert(*pos);
        if (with_robo_santa)
            pos = pos == &santa_pos
                ? &robot_pos
                : &santa_pos;
    }
    return visited.size();
}

ostream& solutions::solution1503::operator<<(ostream &os, Position &position)
{
    os << '(' << position.x << ',' << position.y <<')';
    return os;
}

bool solutions::solution1503::operator<(const Position &pos1, const Position &pos2)
{
    return pos1.x == pos2.x
        ? pos1.y < pos2.y
        : pos1.x < pos2.x;
}

bool solutions::solution1503::operator==(const Position &pos1, const Position &pos2)
{
    return pos1.x == pos2.x && pos1.y == pos2.y;
}
