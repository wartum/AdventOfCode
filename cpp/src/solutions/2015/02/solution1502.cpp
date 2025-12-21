#include "solutions.hpp"
#include "solution1502.hpp"
#include <array>
#include <algorithm>
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

int Box::ribbon_length()
{
    array<int, 3> dimensions {length, width, height};
    sort(dimensions.begin(), dimensions.end());
    return 2 * (dimensions[0] + dimensions[1]) + (length * width * height);
}

Solution solutions::solution1502::solve(stringstream &input)
{
    string line;
    int wrapping_paper_sum = 0, ribbon_sum = 0;
    try
    {
        while(getline(input, line))
        {
            Box box(line);
            wrapping_paper_sum += box.wrapping_paper_area();
            ribbon_sum += box.ribbon_length();
        }
    }
    catch (InvalidInputException &ex)
    {
        cerr << ex.what() << "\n";
        return {};
    }


    return {
        to_string(wrapping_paper_sum),
        to_string(ribbon_sum)
    };
}
