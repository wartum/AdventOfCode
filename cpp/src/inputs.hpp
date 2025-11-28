#pragma once
#include <sstream>
#include <optional>

namespace inputs
{
    std::optional<std::stringstream> get_input(int year, int day, bool use_cache = true);
}
