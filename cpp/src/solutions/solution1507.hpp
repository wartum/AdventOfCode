#pragma once

#include <cstdint>
#include <variant>
#include <optional>
#include <tuple>
#include <vector>
#include <unordered_map>

namespace solutions::solution1507
{
    struct Wire;
    struct Gate;

    typedef uint16_t Signal;
    typedef std::variant<Signal, Wire, Gate> Element;

    enum Operation
    {
        NOT,
        OR,
        AND,
        LSHIFT,
        RSHIFT
    };

    Operation parse_operation(const std::string &operation);

    struct Gate
    {
        std::string id;
        std::optional<uint16_t> signal;
        Operation operation;
        Element *src1;
        Element *src2;
        std::vector<Element*> dst;
    };

    struct Wire
    {
        std::string id;
        std::optional<uint16_t> signal;
        Element *src;
        std::vector<Element*> dst;
    };

    std::unordered_map<std::string, Element> build_circuit(std::stringstream &input);
    void rewire_circuit(std::unordered_map<std::string, Element> &circuit);
    void simulate_circuit(std::unordered_map<std::string, Element> &circuit);
    std::tuple<std::string, std::string> split_signal_descriptor(const std::string &descriptor);
    Element create_element(const std::string &descriptor, std::unordered_map<std::string, Element> &circuit);
}