use std::env::args;

use crate::Result;

pub struct Params {
    pub year: u32,
    pub day: u8,
}

pub fn parse() -> Result<Params> {
    let mut year = None;
    let mut day = None;

    let mut index = 0;
    let params: Vec<String> = args().collect();
    while index < params.len() {
        match params[index].as_str() {
            "-y" | "--year" => {
                year = params.get(index + 1).and_then(|y| y.parse().ok());
            }
            "-d" | "--day" => {
                day = params.get(index + 1).and_then(|d| d.parse().ok());
            }
            _ => {}
        }
        index += 1;
    }

    Ok(Params {
        year: year.ok_or("Year not provided or invalid")?,
        day: day.ok_or("Day not provided or invalid")?,
    })
}
