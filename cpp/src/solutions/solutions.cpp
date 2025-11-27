#include "solutions.hpp"

using namespace std;
using namespace solutions;

ostream& solutions::operator<<(ostream& os, Solution &solution)
{
    os << "* : "
       << (solution.one_star.has_value() ? solution.one_star.value() : "No solution found")
       << "\n"
       << "**: "
       << (solution.two_star.has_value() ? solution.two_star.value() : "No solution found");
    return os;
}

Solution solutions::solve(int year, int day, const string &input)
{
    switch (year)
    {
        case 2015:
            switch (day)
            {
                case 1: return solution1501::solve(input);
                case 2: return solution1502::solve(input);
            }
    }

    return {};
}
