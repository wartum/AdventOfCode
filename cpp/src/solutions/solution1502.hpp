#pragma once
#include <string>
namespace solutions::solution1502
{
    struct Box
    {
        int length;
        int width;
        int height;

        Box() = delete;
        Box(int l, int w, int h);
        Box(const std::string &description);

        int wrapping_paper_area();
        int ribbon_length();
    };

    std::ostream& operator<<(std::ostream &os, Box &box);
}
