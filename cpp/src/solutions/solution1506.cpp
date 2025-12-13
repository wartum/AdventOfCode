#include <sstream>
#include <string>
#include <numeric>

#include "solutions.hpp"
#include "solution1506.hpp"

using namespace std;
using namespace solutions;

namespace solutions::solution1506
{
    Solution solve(stringstream &input)
    {
        Grid grid, grid2;
        string line;

        while(getline(input, line))
        {
            grid.execute(read_instruction(line));
            grid2.execute_2(read_instruction(line));
        }
        
        return {
            to_string(grid.count_turned_on()),
            to_string(grid2.count_turned_on()),
        };
    }

    Instruction read_instruction(const std::string &line)
    {
        stringstream ss(line);
        string token;
        Action action;
        Position pos1, pos2;
        bool through = false;

        while(!ss.eof())
        {
            ss >> token;
            if (token == "toggle")
                action = Action::TOGGLE;
            else if(token == "turn")
                continue;
            else if(token == "on")
                action = Action::ON;
            else if(token == "off")
                action = Action::OFF;
            else if(token == "through")
                through = true;
            else if (!through)
                pos1 = read_position(token);
            else 
                pos2 = read_position(token);
        }
        return {action, pos1, pos2};
    }

    Position read_position(const std::string &line)
    {
        stringstream n1, n2;
        bool next = false;
        for (char c : line)
        {
            if (c == ',')
            {
                next = true;
                continue;
            }

            if (!next)
                n1 << c;
            else
                n2 << c;
        }

        return {stoi(n1.str()), stoi(n2.str())};
    }
    
    Grid::Grid()
    {
        lights.fill(0);
    }

    int& Grid::get_light(int x, int y)
    {
        return lights.at(y * GRID_HEIGHT + x);
    }

    size_t Grid::count_turned_on()
    {
        return accumulate(lights.begin(), lights.end(), 0);
    }

    void Grid::execute(Instruction instruction)
    {
        auto [action, pos1, pos2] = instruction;
        int x = get<0>(pos1), y = get<1>(pos1);
        while (y <= get<1>(pos2))
        {
            switch (action)
            {
            case Action::ON:
                get_light(x, y) = 1;
                break;
            case Action::OFF:
                get_light(x, y) = 0;
                break;
            case Action::TOGGLE:
                get_light(x, y) = get_light(x, y) == 0 ? 1 : 0;
                break;
            }

            x += 1;
            if (x > get<0>(pos2))
            {
                x = get<0>(pos1);
                y += 1;
            }
        }
    }

    void Grid::execute_2(Instruction instruction)
    {
        auto [action, pos1, pos2] = instruction;
        int x = get<0>(pos1), y = get<1>(pos1);
        while (y <= get<1>(pos2))
        {
            switch (action)
            {
            case Action::ON:
                get_light(x, y) += 1;
                break;
            case Action::OFF:
                if (get_light(x, y) > 0)
                    get_light(x, y) -= 1;
                break;
            case Action::TOGGLE:
                get_light(x, y) += 2;
                break;
            }

            x += 1;
            if (x > get<0>(pos2))
            {
                x = get<0>(pos1);
                y += 1;
            }
        }
    }
}