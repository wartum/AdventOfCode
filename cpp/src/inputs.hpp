#pragma once
#include <string>
#include <optional>

namespace inputs
{
    std::optional<std::string> get_input(int year, int day, bool use_cache = true);
}
