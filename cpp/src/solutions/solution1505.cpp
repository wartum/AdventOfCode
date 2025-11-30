#include <iostream>
#include <sstream>
#include <array>
#include <map>
#include <algorithm>

#include "solutions.hpp"
#include "solution1505.hpp"

using namespace std;
using namespace solutions;

namespace solutions::solution1505
{
    Solution solve(stringstream &input)
    {
        string line;
        int nice_count = 0, nice_2_count = 0;
        while (getline(input, line))
        {
            if (is_nice(line))
                nice_count += 1;
            if (is_nice_2(line))
                nice_2_count += 1;
        }
        return {
            to_string(nice_count),
            to_string(nice_2_count),
        };
    }

    bool is_nice(const string &str)
    {
        return contains_three_vowels(str)
            && letter_twice(str)
            && !contains_blacklisted_strings(str);
    }

    bool is_nice_2(const string &str)
    {
        return contains_pair_twice(str)
            && contains_letter_between_pair(str);
    }

    bool contains_three_vowels(const string &str)
    {
        array<char, 5> vowels {'a', 'e', 'i', 'o', 'u'};
        return count_if(str.begin(), str.end(), [&](const char c)
            {
                return find(vowels.begin(), vowels.end(), c) != vowels.end();
            }) >= 3;
    }

    bool contains_blacklisted_strings(const string &str)
    {
        array<string, 4> blacklist {"ab", "cd", "xy", "pq"};
        for (string &str2 : blacklist)
        {
            if (str.find(str2) != string::npos)
                return true;
        }
        return false;
    }

    bool letter_twice(const std::string &str)
    {
        optional<char> prev_c = {};
        for (char c : str)
        {
            if (prev_c.has_value())
            {
                if (c == prev_c.value())
                    return true;
            }
            prev_c = c;
        }
        return false;
    }

    bool contains_pair_twice(const string &str)
    {
        map<string, int> pairs_cnt;
        optional<string> pr_pair = {}, prpr_pair = {};
        bool overlapping = false;
        for (int i = 0; i < str.size()-1; i++)
        {
            string pair = str.substr(i, 2);
            if (pr_pair.has_value() && pr_pair.value() == pair)
            {
                overlapping = true;
                if (prpr_pair.has_value() && prpr_pair.value() == pair)
                    overlapping = false;
            }

            if (!overlapping)
                pairs_cnt[pair] += 1;

            if (pr_pair.has_value())
                prpr_pair = pr_pair.value();
            pr_pair = pair;
            overlapping = false;
        }

        return any_of(pairs_cnt.begin(), pairs_cnt.end(), [](auto &p)
            {
                return p.second >= 2;
            });

        for (auto &pair : pairs_cnt)
        {
            cout << pair.first << " = " << pair.second << '\n';
        }
        return false;
    }

    bool contains_letter_between_pair(const string &str)
    {
        for (int i = 0; i < str.size()-2 ; i++)
        {
            if (str[i] == str[i+2])
                return true;
        }
        return false;
    }
}
