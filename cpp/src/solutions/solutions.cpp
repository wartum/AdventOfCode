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

Solution solutions::solve(int year, int day, stringstream &input)
{
    switch (year)
    {
        case 2015:
            switch (day)
            {
                case 1: return solution1501::solve(input);
                case 2: return solution1502::solve(input);
                case 3: return solution1503::solve(input);
                case 4: return solution1504::solve(input);
                case 5: return solution1505::solve(input);
                case 6: return solution1506::solve(input);
                case 7: return solution1507::solve(input);
            }
    }

    return {};
}
