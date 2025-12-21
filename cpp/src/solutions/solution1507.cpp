#include <iostream>
#include <sstream>
#include <algorithm>

#include "solutions.hpp"
#include "solution1507.hpp"

using namespace std;
using namespace solutions;

namespace solutions::solution1507
{
    Solution solve(stringstream &input)
    {
        try
        {
            auto circuit = build_circuit(input);
            simulate_circuit(circuit);

            if (!circuit.contains("a"))
                throw InvalidInputException("No 'a' signal provided");

            if (get<Wire>(circuit["a"]).src == nullptr)
                throw runtime_error("Wire 'a' doesn't have source connected");

            if (!get<Wire>(circuit["a"]).signal.has_value())
                throw runtime_error("Wire 'a' doesn't receive signal");

            Signal original_a = get<Wire>(circuit["a"]).signal.value();

            rewire_circuit(circuit);
            simulate_circuit(circuit);

            if (!circuit.contains("a"))
                throw InvalidInputException("No 'a' signal provided");

            if (get<Wire>(circuit["a"]).src == nullptr)
                throw runtime_error("Wire 'a' doesn't have source connected");

            if (!get<Wire>(circuit["a"]).signal.has_value())
                throw runtime_error("Wire 'a' doesn't receive signal");

            Signal new_a = get<Wire>(circuit["a"]).signal.value();
            
            return {
                to_string(original_a),
                to_string(new_a),
            };
        }
        catch (exception &e)
        {
            cerr << "ERROR: " << e.what() << endl;
            return {};
        }
    }

    Operation parse_operation(const string &operation)
    {
        if (operation == "NOT")
            return Operation::NOT;
        if (operation == "OR")
            return Operation::OR;
        if (operation == "AND")
            return Operation::AND;
        if (operation == "LSHIFT")
            return Operation::LSHIFT;
        if (operation == "RSHIFT")
            return Operation::RSHIFT;
        throw InvalidInputException("Operation not supported");
    }

    tuple<string, string> split_signal_descriptor(const string &descriptor)
    {
        size_t split_pos = descriptor.find("->");
        if (split_pos == string::npos)
            throw InvalidInputException("Delimiter '->' not found");
        
        const string lh = descriptor.substr(0, split_pos - 1);
        const string rh = descriptor.substr(split_pos + 3);
        return {lh, rh};
    }

    bool is_signal(const string &descriptor)
    {
        return all_of(descriptor.begin(), descriptor.end(), isdigit);
    }

    bool is_gate(const string &descriptor)
    {
        return any_of(descriptor.begin(), descriptor.end(), isspace);
    }

    Element create_signal(const string &descriptor)
    {
        return Signal(stoi(descriptor));
    }

    Element create_gate(const string &descriptor, unordered_map<string, Element> &circuit)
    {
        stringstream tokenizer(descriptor);
        string src1, src2, operation;
        tokenizer >> src1;
        if (src1 == "NOT")
        {
            operation = src1;
            tokenizer >> src1;
        }
        else
        {
            tokenizer >> operation;
            tokenizer >> src2;
        }

        if (!circuit.contains(src1))
            circuit[src1] = is_signal(src1)
                ? create_signal(src1)
                : Wire(src1);

        if (operation == "NOT")
            return Gate(descriptor, {}, parse_operation(operation), &circuit[src1], nullptr);

        if (!circuit.contains(src2))
            circuit[src2] = is_signal(src2)
                ? create_signal(src2)
                : Wire(src2);
        
        return Gate(descriptor, {}, parse_operation(operation), &circuit[src1], &circuit[src2]);
    }

    Element create_element(const string &descriptor, unordered_map<string, Element> &circuit)
    {
        if (is_signal(descriptor))
            return create_signal(descriptor);
        if (is_gate(descriptor))
            return create_gate(descriptor, circuit);

        return Wire(descriptor);
    }

    void establish_mutual_connection_with_src(Gate &gate, unordered_map<string, Element> &circuit)
    {
        if (gate.src1 == nullptr)
            throw runtime_error("src1 is nullptr");

        if (holds_alternative<Wire>(*gate.src1))
        {
            Wire &src = get<Wire>(*gate.src1);
            if (find(src.dst.begin(), src.dst.end(), &circuit[gate.id]) == src.dst.end())
                src.dst.push_back(&circuit[gate.id]);
        }
        if (holds_alternative<Gate>(*gate.src1))
        {
            Gate &src = get<Gate>(*gate.src1);
            if (find(src.dst.begin(), src.dst.end(), &circuit[gate.id]) == src.dst.end())
                src.dst.push_back(&circuit[gate.id]);
        }

        if (gate.operation == Operation::NOT)
            return;

        if (gate.src2 == nullptr)
            throw runtime_error("src2 is nullptr");

        if (holds_alternative<Wire>(*gate.src2))
        {
            Wire &src = get<Wire>(*gate.src2);
            if (find(src.dst.begin(), src.dst.end(), &circuit[gate.id]) == src.dst.end())
                src.dst.push_back(&circuit[gate.id]);
        }
        if (holds_alternative<Gate>(*gate.src2))
        {
            Gate &src = get<Gate>(*gate.src2);
            if (find(src.dst.begin(), src.dst.end(), &circuit[gate.id]) == src.dst.end())
                src.dst.push_back(&circuit[gate.id]);
        }
    }

    void establish_mutual_connection_with_src(Wire &wire, unordered_map<string, Element> &circuit)
    {
        if (holds_alternative<Wire>(*wire.src))
        {
            Wire &src = get<Wire>(*wire.src);
            if (find(src.dst.begin(), src.dst.end(), &circuit[wire.id]) == src.dst.end())
                src.dst.push_back(&circuit[wire.id]);
        }
        if (holds_alternative<Gate>(*wire.src))
        {
            Gate &src = get<Gate>(*wire.src);
            if (find(src.dst.begin(), src.dst.end(), &circuit[wire.id]) == src.dst.end())
                src.dst.push_back(&circuit[wire.id]);
        }
    }

    unordered_map<string, Element> build_circuit(stringstream &input)
    {
        unordered_map<string, Element> circuit;
        string descriptor;
        while (getline(input, descriptor))
        {
            auto [lh_id, rh_id] = split_signal_descriptor(descriptor);
            if (!circuit.contains(lh_id))
                circuit[lh_id] = create_element(lh_id, circuit);
            
            if (!circuit.contains(rh_id))
            {
                Wire rh(rh_id);
                rh.src = &circuit[lh_id];
                circuit[rh_id] = rh;
            }
            else
            {
                Wire &rh = get<Wire>(circuit[rh_id]);
                rh.src = &circuit[lh_id];
            }

            if (holds_alternative<Gate>(circuit[lh_id]))
            {
                Gate &gate = get<Gate>(circuit[lh_id]);
                gate.dst.push_back(&circuit[rh_id]);
                establish_mutual_connection_with_src(gate, circuit);
            }
            else if (holds_alternative<Wire>(circuit[lh_id]))
            {
                Wire &wire = get<Wire>(circuit[lh_id]);
                wire.dst.push_back(&circuit[rh_id]);
                int x = 5;
            }
        }
        return circuit;
    }

    void simulate_circuit(unordered_map<string, Element> &circuit)
    {
        bool dirty = true;
        while(dirty)
        {
            dirty = false;
            for (auto &pair : circuit)
            {
                if (holds_alternative<Wire>(pair.second))
                {
                    Wire &w = get<Wire>(pair.second);
                    if (!w.signal.has_value())
                    {
                        if (holds_alternative<Signal>(*w.src))
                            w.signal = get<Signal>(*w.src);
                        else if (holds_alternative<Wire>(*w.src))
                            w.signal = get<Wire>(*w.src).signal;
                        else if (holds_alternative<Gate>(*w.src))
                            w.signal = get<Gate>(*w.src).signal;
    
                        if (w.signal.has_value())
                            dirty = true;
                    }
                }
                else if (holds_alternative<Gate>(pair.second))
                {
                    Gate &g = get<Gate>(pair.second);
                    if (!g.signal.has_value())
                    {
                        optional<Signal> sig1, sig2;
                        if (holds_alternative<Signal>(*g.src1))
                            sig1 = get<Signal>(*g.src1);
                        else if (holds_alternative<Wire>(*g.src1))
                            sig1 = get<Wire>(*g.src1).signal;
                        else if (holds_alternative<Gate>(*g.src1))
                            sig1 = get<Gate>(*g.src1).signal;

                        if (g.operation == NOT)
                        {
                            if (sig1.has_value())
                                g.signal = ~sig1.value();
                        }
                        else
                        {
                            if (holds_alternative<Signal>(*g.src2))
                                sig2 = get<Signal>(*g.src2);
                            else if (holds_alternative<Wire>(*g.src2))
                                sig2 = get<Wire>(*g.src2).signal;
                            else if (holds_alternative<Gate>(*g.src2))
                                sig2 = get<Gate>(*g.src2).signal;
    
                            if (sig1.has_value() && sig2.has_value())
                            {
                                switch(g.operation)
                                {
                                    case OR: g.signal = sig1.value() | sig2.value(); break;
                                    case AND: g.signal = sig1.value() & sig2.value(); break;
                                    case LSHIFT: g.signal = sig1.value() << sig2.value(); break;
                                    case RSHIFT: g.signal = sig1.value() >> sig2.value(); break;
                                }
                            }
                        }

                        if (g.signal.has_value())
                            dirty = true;
                    }
                }
            }
        }
    }
    
    void rewire_circuit(unordered_map<string, Element> &circuit)
    {
        Wire &a = get<Wire>(circuit["a"]);
        Wire &b = get<Wire>(circuit["b"]);
        Signal signal = a.signal.value();
        circuit[to_string(signal)] = signal;
        b.src = &circuit[to_string(signal)];
        a.dst.push_back(&circuit["b"]);

        for (auto &pair : circuit)
        {
            if (holds_alternative<Wire>(pair.second))
            {
                Wire &wire = get<Wire>(pair.second);
                wire.signal = {};
            }
            if (holds_alternative<Gate>(pair.second))
            {
                Gate &gate = get<Gate>(pair.second);
                gate.signal = {};
            }
        }
    }
}