#pragma once
#include <cstdint>
#include <tuple>
#include <variant>

namespace solutions::solution1507
{
    enum Operation
    {
        NOT,
        OR,
        AND,
        LSHIFT,
        RSHIFT
    };

    struct Constant;
    struct Wire;
    struct Gate;
    typedef std::variant<Constant, Wire, Gate> SignalEmitter;
    
    struct Constant
    {
        uint16_t value;
        std::string name;
    };
    
    struct Wire
    {
        SignalEmitter* in;
        std::string name;
    };
    
    struct Gate
    {
        Operation operationType;
        SignalEmitter* in1;
        SignalEmitter* in2;
        std::string name;
    };
    
    bool operator==(const Constant &lh, const Constant &rh);
    bool operator==(const Wire &lh, const Wire &rh);
    bool operator==(const Gate &lh, const Gate &rh);

    Operation parse_operation(const std::string operation);
    uint16_t evaluate(const SignalEmitter &node);
    uint16_t evaluate_gate(const Gate &gate);
    std::tuple<std::string, std::string> split_signal_definition(const std::string &line);
    std::string get_signal_map_key(const std::string &signal);
    SignalEmitter get_signal_map_value(const std::string &signal, std::unordered_map<std::string, SignalEmitter> &nodes);
}