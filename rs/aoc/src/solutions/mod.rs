mod solution1501;

use crate::Result;

pub struct Solution {
    pub one_star: Result<String>,
    pub two_star: Result<String>,
}

impl Default for Solution {
    fn default() -> Self {
        Solution {
            one_star: Err("No solution for given puzzle".into()),
            two_star: Err("No solution for given puzzle".into()),
        }
    }
}

pub fn solve(year: u32, day: u8, input: String) -> Solution {
    match (year, day) {
        (2015, 1) => solution1501::solve(input),
        _ => Solution::default()
    }
}