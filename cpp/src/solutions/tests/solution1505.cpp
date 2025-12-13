#include <gtest/gtest.h>

#include "solution1505.hpp"

using namespace solutions::solution1505;

TEST(solution1505, three_vowels)
{
    ASSERT_EQ(contains_three_vowels("aei"), true);
    ASSERT_EQ(contains_three_vowels("xazegov"), true);
    ASSERT_EQ(contains_three_vowels("aeiouaeiouaeiou"), true);
    ASSERT_EQ(contains_three_vowels("xyz"), false);
    ASSERT_EQ(contains_three_vowels("axy"), false);
    ASSERT_EQ(contains_three_vowels("aexyu"), true);
}

TEST(solution1505, letter_twice)
{
    ASSERT_EQ(letter_twice("xx"), true);
    ASSERT_EQ(letter_twice("abcdde"), true);
    ASSERT_EQ(letter_twice("aabbccdd"), true);
    ASSERT_EQ(letter_twice("xyx"), false);
    ASSERT_EQ(letter_twice("abcde"), false);
}

TEST(solution1505, contains_blacklisted_strings)
{
    ASSERT_EQ(contains_blacklisted_strings("abcde"), true);
    ASSERT_EQ(contains_blacklisted_strings("bbbcde"), true);
    ASSERT_EQ(contains_blacklisted_strings("xxxpq"), true);
    ASSERT_EQ(contains_blacklisted_strings("xxxypp"), true);
    ASSERT_EQ(contains_blacklisted_strings("asdf"), false);
}

TEST(solution1505, contains_pair_twice)
{
    ASSERT_EQ(contains_pair_twice("abcde"), false);
    ASSERT_EQ(contains_pair_twice("qjabqj"), true);
    ASSERT_EQ(contains_pair_twice("aaaa"), true);
    ASSERT_EQ(contains_pair_twice("aaa"), false);
    ASSERT_EQ(contains_pair_twice("bbabb"), true);
    ASSERT_EQ(contains_pair_twice("bbbabb"), true);
    ASSERT_EQ(contains_pair_twice("bbbbabb"), true);
    ASSERT_EQ(contains_pair_twice("bcbbabb"), true);
}

TEST(solution1505, contains_letter_between_pair)
{
    ASSERT_EQ(contains_letter_between_pair("xyx"), true);
    ASSERT_EQ(contains_letter_between_pair("yyx"), false);
    ASSERT_EQ(contains_letter_between_pair("aaa"), true);
}

TEST(solution1505, is_nice)
{
    ASSERT_EQ(is_nice("jchzalrnumimnmhp"), false);
    ASSERT_EQ(is_nice("haegwjzuvuyypxyu"), false);
    ASSERT_EQ(is_nice("dvszwmarrgswjxmb"), false);
}

TEST(solution1505, is_nice_2)
{
    ASSERT_EQ(is_nice_2("qjhvhtzxzqqjkmpb"), true);
    ASSERT_EQ(is_nice_2("xxyxx"), true);
    ASSERT_EQ(is_nice_2("uurcxstgmygtbstg"), false);
    ASSERT_EQ(is_nice_2("ieodomkazucvgmuy"), false);
}
