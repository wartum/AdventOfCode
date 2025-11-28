#pragma once
#include <ostream>
#include <string>
#include <optional>

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

    namespace solution1501 {
        Solution solve(std::stringstream &input);
    }
    namespace solution1502 {
        Solution solve(std::stringstream &input);
    }
    namespace solution1503 {
        Solution solve(std::stringstream &input);
    }
}
