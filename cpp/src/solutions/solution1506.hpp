#pragma once
#include <memory>
#include <array>

const int GRID_WIDTH = 1000;
const int GRID_HEIGHT = 1000;

namespace solutions::solution1506
{
    enum class Action
    {
        ON,
        OFF,
        TOGGLE
    };

    typedef std::tuple<int, int> Position;
    typedef std::tuple<Action, Position, Position> Instruction;

    struct Grid
    {
        Grid();
        void execute(Instruction instruction);
        void execute_2(Instruction instruction);
        int& get_light(int x, int y);
        size_t count_turned_on();

        std::unique_ptr<std::array<int, GRID_WIDTH * GRID_HEIGHT>> lights; 
    };

    Position read_position(const std::string &line);
    Instruction read_instruction(const std::string &line);
}