mod tests;

use super::Solution;

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
        one_star: Ok(format!("{}", current_floor).into()),
        two_star: match basement_position {
            Some(pos) => Ok(format!("{}", pos).into()),
            None => Err("Never enters basement".into()),
        }
    }
}