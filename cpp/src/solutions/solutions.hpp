#pragma once
#include <ostream>
#include <string>
#include <optional>

#define DECLARE_SOLUTION(x) namespace solution##x { Solution solve(std::stringstream &input); }

namespace solutions
{
    class InvalidInputException : public std::exception
    {
        public:
            InvalidInputException(const char* message) :
                message(message) {}
            const char* what() const noexcept override
                { return message; }
        private:
            const char* message;
    };

    struct Solution
    {
        std::optional<std::string> one_star;
        std::optional<std::string> two_star;
    };

    std::ostream& operator<<(std::ostream& os, Solution &solution);
    Solution solve(int year, int day, std::stringstream &input);

    DECLARE_SOLUTION(1501)
    DECLARE_SOLUTION(1502)
    DECLARE_SOLUTION(1503)
    DECLARE_SOLUTION(1504)
    DECLARE_SOLUTION(1505)
    DECLARE_SOLUTION(1506)
    DECLARE_SOLUTION(1507)
}

#undef DECLARE_SOLUTION