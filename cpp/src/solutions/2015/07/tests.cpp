#include <gtest/gtest.h>
#include <array>
#include <unordered_map>
#include <algorithm>

#include "solution1507.hpp"

using namespace solutions::solution1507;
using namespace std;

TEST(solution1507, split_signal_descriptor)
{
    const string in1 = "NOT dq -> dr";
    const string in2 = "kg OR kf -> kh";
    const string in3 = "44430 -> b";
    const tuple<string, string> out1 = split_signal_descriptor(in1);
    const tuple<string, string> out2 = split_signal_descriptor(in2);
    const tuple<string, string> out3 = split_signal_descriptor(in3);

    ASSERT_EQ(get<0>(out1), "NOT dq");
    ASSERT_EQ(get<1>(out1), "dr");
    ASSERT_EQ(get<0>(out2), "kg OR kf");
    ASSERT_EQ(get<1>(out2), "kh");
    ASSERT_EQ(get<0>(out3), "44430");
    ASSERT_EQ(get<1>(out3), "b");
}

TEST(solution1507, connect_wires)
{
    stringstream input;
    input << "1 -> a\n";
    input << "a -> b\n";
    input << "c -> d\n";
    input << "b -> c\n";

    auto circuit = build_circuit(input);
    ASSERT_EQ(circuit.size(), 5);

    auto a = get<Wire>(circuit["a"]);
    auto b = get<Wire>(circuit["b"]);
    auto c = get<Wire>(circuit["c"]);
    auto d = get<Wire>(circuit["d"]);

    ASSERT_EQ(a.dst.size(), 1);
    ASSERT_NE(a.src, nullptr);
    ASSERT_EQ(b.dst.size(), 1);
    ASSERT_NE(b.src, nullptr);
    ASSERT_EQ(c.dst.size(), 1);
    ASSERT_NE(c.src, nullptr);
    ASSERT_EQ(d.dst.size(), 0);
    ASSERT_NE(d.src, nullptr);
}

TEST(solution1507, build_circuit)
{
    stringstream input;
    input << "123 -> x\n";
    input << "456 -> y\n";
    input << "x AND y -> d\n";
    input << "x OR y -> e\n";
    input << "x LSHIFT 2 -> f\n";
    input << "y RSHIFT 2 -> g\n";
    input << "NOT x -> h\n";
    input << "NOT y -> i\n";

    auto circuit = build_circuit(input);
    ASSERT_EQ(circuit.size(), 17);

    auto d = get<Wire>(circuit["d"]);
    auto e = get<Wire>(circuit["e"]);
    auto f = get<Wire>(circuit["f"]);
    auto g = get<Wire>(circuit["g"]);
    auto h = get<Wire>(circuit["h"]);
    auto i = get<Wire>(circuit["i"]);
    auto x = get<Wire>(circuit["x"]);
    auto y = get<Wire>(circuit["y"]);

    auto xANDy = get<Gate>(circuit["x AND y"]);
    auto xORy = get<Gate>(circuit["x OR y"]);
    auto xLSHIFT2 = get<Gate>(circuit["x LSHIFT 2"]);
    auto yRSHIFT2 = get<Gate>(circuit["y RSHIFT 2"]);
    auto NOTx = get<Gate>(circuit["NOT x"]);
    auto NOTy = get<Gate>(circuit["NOT y"]);

    ASSERT_EQ(x.src, &circuit["123"]);
    ASSERT_EQ(x.dst.size(), 4);
    ASSERT_EQ(y.src, &circuit["456"]);
    ASSERT_EQ(y.dst.size(), 4);

    ASSERT_EQ(d.src, &circuit["x AND y"]);
    ASSERT_EQ(xANDy.dst.size(), 1);
    ASSERT_NE(find(xANDy.dst.begin(), xANDy.dst.end(), &circuit["d"]), xANDy.dst.end());

    ASSERT_EQ(e.src, &circuit["x OR y"]);
    ASSERT_EQ(xORy.dst.size(), 1);
    ASSERT_NE(find(xORy.dst.begin(), xORy.dst.end(), &circuit["e"]), xORy.dst.end());

    ASSERT_EQ(f.src, &circuit["x LSHIFT 2"]);
    ASSERT_EQ(xLSHIFT2.dst.size(), 1);
    ASSERT_NE(find(xLSHIFT2.dst.begin(), xLSHIFT2.dst.end(), &circuit["f"]), xLSHIFT2.dst.end());

    ASSERT_EQ(g.src, &circuit["y RSHIFT 2"]);
    ASSERT_EQ(yRSHIFT2.dst.size(), 1);
    ASSERT_NE(find(yRSHIFT2.dst.begin(), yRSHIFT2.dst.end(), &circuit["g"]), yRSHIFT2.dst.end());

    ASSERT_EQ(h.src, &circuit["NOT x"]);
    ASSERT_EQ(NOTx.dst.size(), 1);
    ASSERT_NE(find(NOTx.dst.begin(), NOTx.dst.end(), &circuit["h"]), NOTx.dst.end());

    ASSERT_EQ(i.src, &circuit["NOT y"]);
    ASSERT_EQ(NOTy.dst.size(), 1);
    ASSERT_NE(find(NOTy.dst.begin(), NOTy.dst.end(), &circuit["i"]), NOTy.dst.end());
}

TEST(solution1507, simulate_circuit)
{
    stringstream input;
    input << "123 -> x\n";
    input << "456 -> y\n";
    input << "x AND y -> d\n";
    input << "x OR y -> e\n";
    input << "x LSHIFT 2 -> f\n";
    input << "y RSHIFT 2 -> g\n";
    input << "NOT x -> h\n";
    input << "NOT y -> i\n";

    auto circuit = build_circuit(input);
    simulate_circuit(circuit);

    auto d = get<Wire>(circuit["d"]);
    auto e = get<Wire>(circuit["e"]);
    auto f = get<Wire>(circuit["f"]);
    auto g = get<Wire>(circuit["g"]);
    auto h = get<Wire>(circuit["h"]);
    auto i = get<Wire>(circuit["i"]);
    auto x = get<Wire>(circuit["x"]);
    auto y = get<Wire>(circuit["y"]);

    ASSERT_TRUE(d.signal.has_value());
    ASSERT_TRUE(e.signal.has_value());
    ASSERT_TRUE(f.signal.has_value());
    ASSERT_TRUE(g.signal.has_value());
    ASSERT_TRUE(h.signal.has_value());
    ASSERT_TRUE(i.signal.has_value());
    ASSERT_TRUE(x.signal.has_value());
    ASSERT_TRUE(y.signal.has_value());

    ASSERT_EQ(d.signal.value(), 72);
    ASSERT_EQ(e.signal.value(), 507);
    ASSERT_EQ(f.signal.value(), 492);
    ASSERT_EQ(g.signal.value(), 114);
    ASSERT_EQ(h.signal.value(), 65412);
    ASSERT_EQ(i.signal.value(), 65079);
    ASSERT_EQ(x.signal.value(), 123);
    ASSERT_EQ(y.signal.value(), 456);
}