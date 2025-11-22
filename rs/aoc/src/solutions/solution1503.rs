use std::collections::HashSet;

use super::Solution;

pub fn solve(input: String) -> Solution {
    Solution {
        one_star: Ok(solve_santa_only(&input)),
        two_star: Ok(solve_robo_santa(&input)),
    }
}

pub fn solve_santa_only(input: &str) -> String {
    let mut santa_x = 0;
    let mut santa_y = 0;

    let mut houses = HashSet::new();
    houses.insert((santa_x, santa_y));

    for c in input.chars() {
        match c {
            '^' => santa_y += 1,
            'v' => santa_y -= 1,
            '>' => santa_x += 1,
            '<' => santa_x -= 1,
            _ => {}
        }
        houses.insert((santa_x, santa_y));
    }

    houses.len().to_string()
}

pub fn solve_robo_santa(input: &str) -> String {
    let mut santa_x = 0;
    let mut santa_y = 0;
    let mut robosanta_x = 0;
    let mut robosanta_y = 0;
    let mut santa_turn = false;

    let mut houses = HashSet::new();
    houses.insert((santa_x, santa_y));

    for c in input.chars() {
        santa_turn = !santa_turn;
        let (x, y) = if santa_turn {
            (&mut santa_x, &mut santa_y)
        } else {
            (&mut robosanta_x, &mut robosanta_y)
        };

        match c {
            '^' => *y += 1,
            'v' => *y -= 1,
            '>' => *x += 1,
            '<' => *x -= 1,
            _ => {}
        }
        houses.insert((*x, *y));
    }

    houses.len().to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn santa_delivery() {
        let test_cases = vec![(">", 2), ("^>v<", 4), ("^v^v^v^v^v", 2)];

        for (input, expected) in test_cases {
            let solution = solve_santa_only(input);
            assert_eq!(solution.parse::<i32>().unwrap(), expected);
        }
    }

    #[test]
    fn robo_santa_delivery() {
        let test_cases = vec![("^v", 3), ("^>v<", 3), ("^v^v^v^v^v", 11)];

        for (input, expected) in test_cases {
            let solution = solve_robo_santa(input);
            assert_eq!(solution.parse::<i32>().unwrap(), expected);
        }
    }
}
