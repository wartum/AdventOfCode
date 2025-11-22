use super::Solution;

pub fn solve(input: String) -> Solution {
    let input = input.trim_ascii();

    let mut number = 0;
    while !try_number(input, number, "00000") {
        number += 1;
    }
    let one_star = Ok(number.to_string());

    number = 0;
    while !try_number(input, number, "000000") {
        number += 1;
    }
    let two_star = Ok(number.to_string());

    Solution { one_star, two_star }
}

pub fn try_number(key: &str, number: u64, condition: &str) -> bool {
    let hash_input = format!("{}{}", key, number);
    let hash_output = format!("{:x}", md5::compute(&hash_input));
    hash_output.starts_with(condition)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn try_hash() {
        let test_cases = vec![("abcdef", 609043), ("pqrstuv", 1048970)];
        for (key, number) in test_cases.iter() {
            assert_eq!(try_number(key, *number, "00000"), true);
        }
    }
}
