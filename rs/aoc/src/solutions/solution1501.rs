use super::solution::Solution;

pub fn solve(input: String) -> Solution {
    let mut current_floor = 0;
    let mut current_position = 0;
    let mut basement_position = None;

    for c in input.chars() {
        current_position += 1;
        match c {
            '(' => current_floor += 1,
            ')' => current_floor -= 1,
            _ => {}
        }
        if basement_position.is_none() && current_floor == -1 {
            basement_position = Some(current_position);
        }
    }

    Solution {
        one_star: Ok(format!("{}", current_floor)),
        two_star: match basement_position {
            Some(pos) => Ok(format!("{}", pos)),
            None => Err("Never enters basement".into()),
        },
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn floor_evaluation() {
        let test_cases = vec![
            ("(())", 0),
            ("()()", 0),
            ("(((", 3),
            ("(()(()(", 3),
            ("))(((((", 3),
            ("())", -1),
            ("))(", -1),
            (")))", -3),
            (")())())", -3),
        ];

        for case in test_cases {
            let input = String::from(case.0);
            let expected_floor = case.1;
            let solution = solve(input);
            assert_eq!(
                solution.one_star.unwrap().to_string(),
                expected_floor.to_string()
            );
        }
    }

    #[test]
    fn basement_position_evaluation() {
        let test_cases = vec![
            (")", 1),
            ("()())", 5),
        ];

        for case in test_cases {
            let input = String::from(case.0);
            let expected_position = case.1;
            let solution = solve(input);
            assert_eq!(solution.two_star.unwrap().to_string(), expected_position.to_string());
        }
    }
}
