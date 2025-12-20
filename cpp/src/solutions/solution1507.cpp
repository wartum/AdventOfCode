#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

#include "solutions.hpp"
#include "solution1507.hpp"

using namespace std;
using namespace solutions;

namespace solutions::solution1507
{

    Solution solve(stringstream &input)
    {
        unordered_map<string, SignalEmitter> nodes;
        string line;
        while (getline(input, line))
        {
            auto [lh, rh] = split_signal_definition(line);
            string rh_key = get_signal_map_key(rh);
            string lh_key = get_signal_map_key(lh);
            cout << rh << ": ";
            nodes[lh_key] = get_signal_map_value(lh, nodes);
            nodes[rh_key] = Wire(&nodes[lh_key], rh_key);
        }

        if (!nodes.contains("a"))
            throw runtime_error("Signal 'a' doesn't exist");

        return {
            to_string(evaluate(nodes["a"])),
            ""
        };
    }

    bool operator==(const Constant &lh, const Constant &rh)
    {
        return lh.value == rh.value;
    }

    bool operator==(const Wire &lh, const Wire &rh)
    {
        return lh.in == rh.in;
    }

    bool operator==(const Gate &lh, const Gate &rh)
    {
        return lh.operationType == rh.operationType &&
            lh.in1 == rh.in1 &&
            lh.in2 == rh.in2;
    }

    Operation parse_operation(const string operation)
    {
        if (operation == "NOT")
            return Operation::NOT;
        if (operation == "AND")
            return Operation::AND;
        if (operation == "OR")
            return Operation::OR;
        if (operation == "LSHIFT")
            return Operation::LSHIFT;
        if (operation == "RSHIFT")
            return Operation::RSHIFT;
        
        throw InvalidInputException("Not supported operation type");
    }

    uint16_t evaluate(const SignalEmitter &node)
    {
        if (holds_alternative<Constant>(node))
        {
            auto n = get<Constant>(node);
            cout << "Evaluate: " << n.name << "\n";
            return n.value;
        }
        else if (holds_alternative<Wire>(node))
        {
            auto wire = get<Wire>(node);
            cout << "Evaluate: " << wire.name << "\n";
            return evaluate(*wire.in);
        }
        else if (holds_alternative<Gate>(node))
        {
            auto gate = get<Gate>(node);
            cout << "Evaluate: " << gate.name << "\n";
            return evaluate_gate(gate);
        }
        else
        {
            throw InvalidInputException("Not supported SignalEmitter");
        }
    }

    uint16_t evaluate_gate(const Gate &gate)
    {
        if (gate.in1 == nullptr)
            throw runtime_error("input1 is empty");
        if (gate.operationType != Operation::NOT && gate.in2 == nullptr)
            throw runtime_error("input2 is empty");

        switch (gate.operationType)
        {
        case NOT:
            return ~evaluate(*gate.in1);
        case OR:
            return evaluate(*gate.in1) | evaluate(*gate.in2);
        case AND:
            return evaluate(*gate.in1) & evaluate(*gate.in2);
        case LSHIFT:
            return evaluate(*gate.in1) << evaluate(*gate.in2);
        case RSHIFT:
            return evaluate(*gate.in1) >> evaluate(*gate.in2);
        default:
            throw runtime_error("Not supported logic operation");
        }
    }

    tuple<string, string> split_signal_definition(const string &line)
    {
        size_t split_index = line.find("->");
        string lh = line.substr(0, split_index);
        string rh = line.substr(split_index + 2);
        lh = lh.substr(0, lh.find_last_not_of(' ') + 1);
        rh = rh.substr(rh.find_first_not_of(' '));
        return {lh, rh};
    }

    string get_signal_map_key(const string &signal)
    {
        string copy(signal);
        copy.erase(remove_if(copy.begin(), copy.end(), ::isspace), copy.end());
        return copy;
    }

    Constant read_as_constant(const string &signal, unordered_map<string, SignalEmitter> &nodes)
    {
        string key = get_signal_map_key(signal);
        if (!nodes.contains(key))
            nodes[key] = Constant(stoi(signal), key);
        cout << key << " = " << "Constant(" << stoi(signal) << ")\n";
        return get<Constant>(nodes[key]);
    }

    Wire read_as_wire(const string &signal, unordered_map<string, SignalEmitter> &nodes)
    {
        string key = get_signal_map_key(signal);
        if (!nodes.contains(key))
            nodes[key] = Wire(nullptr, key);
        cout << key << " = " << "Wire\n";
        return get<Wire>(nodes[key]);
    }

    Gate read_as_gate(const string &signal, unordered_map<string, SignalEmitter> &nodes)
    {
        string key = get_signal_map_key(signal);
        if (!nodes.contains(key))
        {
            stringstream ss(signal);
            string token;

            ss >> token;
            if (token == "NOT")
            {
                ss >> token;
                string in1_key = get_signal_map_key(token);
                if (!nodes.contains(in1_key))
                {
                    if (all_of(token.begin(), token.end(), ::isdigit))
                        nodes[in1_key] = read_as_constant(token, nodes);
                    else
                        nodes[in1_key] = Wire(nullptr, in1_key);
                }
                cout << key << " = " << "Gate(" << Operation::NOT << ", " << in1_key << ", nullptr)\n";
                nodes[key] = Gate(Operation::NOT, &nodes[in1_key], nullptr, key);
            }
            else
            {
                string in1_key = get_signal_map_key(token);
                if (!nodes.contains(in1_key))
                {
                    if (all_of(token.begin(), token.end(), ::isdigit))
                        nodes[in1_key] = read_as_constant(token, nodes);
                    else
                        nodes[in1_key] = Wire(nullptr, in1_key);
                }
    
                ss >> token;
                Operation operation = parse_operation(token);
    
                ss >> token;
                string in2_key = get_signal_map_key(token);
                if (!nodes.contains(in2_key))
                {
                    if (all_of(token.begin(), token.end(), ::isdigit))
                        nodes[in2_key] = read_as_constant(token, nodes);
                    else
                        nodes[in2_key] = Wire(nullptr, in2_key);

                }
                cout << key << " = " << "Gate(" << operation << ", " << in1_key << ", " << in2_key << ")\n";
                nodes[key] = Gate(operation, &nodes[in1_key], &nodes[in2_key], key);
            }

        }
        return get<Gate>(nodes[key]);
    }

    SignalEmitter get_signal_map_value(const string &signal, unordered_map<string, SignalEmitter> &nodes)
    {
        if (all_of(signal.begin(), signal.end(), ::isdigit))
            return read_as_constant(signal, nodes);
        else if (any_of(signal.begin(), signal.end(), ::isspace))
            return read_as_gate(signal, nodes);
        else
            return read_as_wire(signal, nodes);
    }
}