#include <gtest/gtest.h>
#include <array>
#include <unordered_map>

#include "solution1507.hpp"

using namespace solutions::solution1507;
using namespace std;

TEST(solution1507, evaluate)
{
    const uint16_t val1 = 5, val2 = 19, shiftval = 2;
    array<SignalEmitter, 9> nodes
    {
        Constant{val1},
        Constant{val2},
        Gate(Operation::NOT, &nodes[0]),
        Gate(Operation::AND, &nodes[0], &nodes[1]),
        Wire(&nodes[2]),
        Gate(Operation::OR, &nodes[0], &nodes[1]),
        Gate(Operation::LSHIFT, &nodes[1], &nodes[8]),
        Gate(Operation::RSHIFT, &nodes[1], &nodes[8]),
        Constant{shiftval},
    };

    ASSERT_EQ(evaluate(nodes[0]), val1);
    ASSERT_EQ(evaluate(nodes[1]), val2);
    ASSERT_EQ(evaluate(nodes[2]),
        static_cast<uint16_t>(~static_cast<uint16_t>(val1))
    );
    ASSERT_EQ(evaluate(nodes[3]),
        static_cast<uint16_t>(val1) & static_cast<uint16_t>(val2)
    );
    ASSERT_EQ(evaluate(nodes[4]), evaluate(nodes[2]));
    ASSERT_EQ(evaluate(nodes[5]),
        static_cast<uint16_t>(val1) | static_cast<uint16_t>(val2)
    );
    ASSERT_EQ(evaluate(nodes[6]),
        static_cast<uint16_t>(val2) << static_cast<uint16_t>(shiftval)
    );
    ASSERT_EQ(evaluate(nodes[7]),
        static_cast<uint16_t>(val2) >> static_cast<uint16_t>(shiftval)
    );
}

TEST(solution1507, evaluate_advanced)
{
    const uint16_t val1 = 12, val2 = 143, lshift = 2, rshift = 5;
    array<SignalEmitter, 12> nodes
    {
        Constant(val1),
        Constant(val2),
        Constant(lshift),
        Constant(rshift),
        Gate(Operation::OR, &nodes[0], &nodes[1]),
        Gate(Operation::LSHIFT, &nodes[1], &nodes[2]),
        Gate(Operation::RSHIFT, &nodes[0], &nodes[3]),
        Gate(Operation::AND, &nodes[5], &nodes[6]),
        Gate(Operation::AND, &nodes[4], &nodes[7]),
        Wire(&nodes[8]),
        Gate(Operation::NOT, &nodes[9]),
        Wire(&nodes[10]),
    };
    const uint16_t expected = ~( (val1|val2) & ((val2<<lshift) & (val1>>rshift)) );
    ASSERT_EQ(evaluate(nodes[11]), expected);
}

TEST(solution1507, replacing_nodes)
{
    array<SignalEmitter, 4> nodes
    {
        Constant(0),
        Constant(1),
        Constant(2),
        Constant(3),
    };
    ASSERT_EQ(evaluate(nodes[3]), 3);

    nodes[3] = Wire(&nodes[1]);
    ASSERT_EQ(evaluate(nodes[3]), 1);

    nodes[1] = Constant(123);
    ASSERT_EQ(evaluate(nodes[3]), 123);

    nodes[0] = Gate(Operation::AND, &nodes[1], &nodes[2]);
    ASSERT_EQ(evaluate(nodes[0]), static_cast<uint16_t>(123 & 2));
}

TEST(solution1507, split_signal_definition)
{
    const string line = "fw AND fy -> fz";
    const string expected_lh = "fw AND fy";
    const string expected_rh = "fz";
    auto [lh, rh] = split_signal_definition(line);
    ASSERT_EQ(lh, expected_lh);
    ASSERT_EQ(rh, expected_rh);
}

TEST(solution1507, get_signal_map_key)
{
    const string signal1 = "eh";
    const string signal2 = "dz AND ef";
    ASSERT_EQ(get_signal_map_key(signal1), "eh");
    ASSERT_EQ(get_signal_map_key(signal2), "dzANDef");
}

TEST(solution1507, get_signal_map_value)
{
    unordered_map<string, SignalEmitter> nodes;

    ASSERT_EQ(get_signal_map_value("12", nodes), SignalEmitter(Constant(12)));
    ASSERT_EQ(nodes.size(), 1);

    ASSERT_EQ(get_signal_map_value("qw", nodes), SignalEmitter(Wire(nullptr)));
    ASSERT_EQ(nodes.size(), 2);

    ASSERT_EQ(get_signal_map_value("12 AND qw", nodes),
        SignalEmitter(Gate(Operation::AND, &nodes["12"], &nodes["qw"]))
    );
    ASSERT_EQ(nodes.size(), 3);

    ASSERT_EQ(get_signal_map_value("13 OR qw", nodes),
        SignalEmitter(Gate(Operation::OR, &nodes["13"], &nodes["qw"]))
    );
    ASSERT_EQ(nodes.size(), 5);

    ASSERT_EQ(get_signal_map_value("NOT qw", nodes),
        SignalEmitter(Gate(Operation::NOT, &nodes["qw"], nullptr))
    );
    ASSERT_EQ(nodes.size(), 6);
}