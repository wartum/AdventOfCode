use super::solution::Solution;
use std::collections::HashMap;

pub fn solve(input: String) -> Solution {
    let input = input.trim();
    Solution {
        one_star: Ok(input.lines().filter(|s| is_nice(s)).count().to_string()),
        two_star: Ok(input.lines().filter(|s| is_nice_2(s)).count().to_string()),
    }
}

fn is_nice(line: &str) -> bool {
    line.chars().filter(|c| is_vowel(*c)).count() >= 3
        && has_duplicate(line)
        && !contains_blacklisted_strings(line)
}

fn is_vowel(c: char) -> bool {
    c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
}

fn has_duplicate(line: &str) -> bool {
    if line.len() <= 1 {
        return false;
    }

    let mut previous_c = line.chars().next().unwrap();
    for c in line.chars().skip(1) {
        if c == previous_c {
            return true;
        }
        previous_c = c;
    }

    false
}

fn contains_blacklisted_strings(line: &str) -> bool {
    let blacklist = ["ab", "cd", "pq", "xy"];
    for s in blacklist {
        if line.contains(s) {
            return true;
        }
    }
    false
}

fn is_nice_2(line: &str) -> bool {
    contains_repeating_pair(line) && contains_repeat_with_one_between(line)
}

fn contains_repeating_pair(line: &str) -> bool {
    if line.len() <= 1 {
        return false;
    }

    let mut pairs = Vec::new();
    for index in 0..line.len() - 1 {
        pairs.push(&line[index..index + 2]);
    }

    let mut pr_pair = None;
    let mut prpr_pair = None;
    let mut do_insert = true;
    let mut pairs_count = HashMap::new();
    for pair in pairs.iter() {
        if let Some(pr_pair) = pr_pair {
            do_insert = pr_pair != *pair;
            if !do_insert && let Some(prpr_pair) = prpr_pair {
                do_insert = prpr_pair == *pair;
            }
        }

        if do_insert {
            match pairs_count.get(*pair) {
                Some(count) => pairs_count.insert(*pair, *count + 1),
                None => pairs_count.insert(*pair, 1),
            };
        }

        if let Some(pr_pair) = pr_pair {
            prpr_pair = Some(pr_pair);
        }
        pr_pair = Some(*pair);
    }

    pairs_count.iter().any(|pair| *pair.1 >= 2)
}

fn contains_repeat_with_one_between(line: &str) -> bool {
    if line.len() <= 2 {
        return false;
    }

    let mut triplets = Vec::new();
    for index in 0..line.len() - 2 {
        triplets.push(&line[index..index + 3]);
    }
    triplets.iter().any(|t| is_one_between(t))
}

fn is_one_between(triplet: &str) -> bool {
    if triplet.len() != 3 {
        return false;
    }
    let mut chars = triplet.chars();
    let c1 = chars.next().unwrap();
    let c3 = chars.nth(1).unwrap();
    c1 == c3
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn nice() {
        let test_cases = vec![
            ("ugknbfddgicrmopn", true),
            ("aaa", true),
            ("jchzalrnumimnmhp", false),
            ("haegwjzuvuyypxyu", false),
            ("dvszwmarrgswjxmb", false),
        ];
        for (line, expected_nice) in test_cases.iter() {
            assert_eq!(is_nice(line), *expected_nice);
        }
    }

    #[test]
    fn repeating_pairs() {
        let test_cases = vec![
            ("abcde", false),
            ("qjabqj", true),
            ("aaaa", true),
            ("aaa", false),
            ("bbabb", true),
            ("bbbabb", true),
            ("bbbbabb", true),
            ("bcbbabb", true),
        ];
        for (line, expected) in test_cases.iter() {
            assert_eq!(contains_repeating_pair(line), *expected);
        }
    }

    #[test]
    fn nice_2() {
        let test_cases = vec![
            ("qjhvhtzxzqqjkmpb", true),
            ("xxyxx", true),
            ("uurcxstgmygtbstg", false),
            ("ieodomkazucvgmuy", false),
            ("xxxxx", true),
        ];
        for (line, expected) in test_cases.iter() {
            assert_eq!(is_nice_2(line), *expected);
        }
    }
}
