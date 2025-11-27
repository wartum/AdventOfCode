#include "solutions.hpp"
#include "solution1502.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace solutions;
using namespace solutions::solution1502;

Box::Box(int l, int w, int h) :
    length(l),
    width(w),
    height(h)
{}

Box::Box(const string &description)
{
    try
    {
        stringstream buffer(description);
        string dimension;
        if(!getline(buffer, dimension, 'x'))
            throw InvalidInputException("Not enough dimensions were provided");
        length = stoi(dimension);

        if(!getline(buffer, dimension, 'x'))
            throw InvalidInputException("Not enough dimensions were provided");
        width = stoi(dimension);

        if(!getline(buffer, dimension, 'x'))
            throw InvalidInputException("Not enough dimensions were provided");
        height = stoi(dimension);

        if(getline(buffer, dimension, 'x'))
            throw InvalidInputException("Too many dimensions were provided");
    }
    catch (invalid_argument)
    {
        throw InvalidInputException("One of passed parameters is not a number");
    }
}

ostream& solutions::solution1502::operator<<(ostream &os, Box &box)
{
    os << "[ " << box.length << 'x' << box.width << 'x' << box.height << " ]";
    return os;
}

int Box::wrapping_paper_area()
{
    int lw = length * width;
    int wh = width * height;
    int hl = height * length;
    int current_min = lw;
    for (int value : {lw, wh, hl})
        current_min = min(current_min,value);

    return 2 * (lw+wh+hl) + current_min;
}

Solution solutions::solution1502::solve(const string &input)
{
    stringstream lines(input);
    string line;
    int wrapping_paper_sum = 0;
    try
    {
        while(getline(lines, line))
        {
            Box box(line);
            wrapping_paper_sum += box.wrapping_paper_area();
        }
    }
    catch (InvalidInputException &ex)
    {
        cerr << ex.what() << "\n";
        return {};
    }


    return {
        one_star: to_string(wrapping_paper_sum),
        two_star: optional<string>()
    };
}
