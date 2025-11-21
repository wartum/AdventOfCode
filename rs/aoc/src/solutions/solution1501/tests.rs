#[cfg(test)]
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
        assert_eq!(solution.one_star.unwrap().to_string(), expected_floor.to_string());
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