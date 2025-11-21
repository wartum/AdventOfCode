use super::solution::Solution;

struct Box {
    length: u32,
    width: u32,
    height: u32,
}

impl Box {
    fn from_description(desc: &str) -> Option<Self> {
        let dims: Vec<u32> = desc
            .split('x')
            .filter_map(|s| s.parse::<u32>().ok())
            .collect();

        if dims.len() != 3 {
            return None;
        }

        Some(Box {
            length: dims[0],
            width: dims[1],
            height: dims[2],
        })
    }

    fn wrap_area(&self) -> u32 {
        let lw = self.length * self.width;
        let wh = self.width * self.height;
        let hl = self.height * self.length;
        let area = 2 * (lw + wh + hl);
        let slack = *[lw, wh, hl].iter().min().unwrap();
        area + slack
    }

    fn ribbon_length(&self) -> u32 {
        let mut dims = [self.length, self.width, self.height];
        dims.sort();

        (2 * dims[0] + 2 * dims[1]) + (self.length * self.width * self.height)
    }
}

pub fn solve(input: String) -> Solution {
    let mut total_area = 0;
    let mut total_ribbon = 0;
    for line in input.lines() {
        if let Some(gift) = Box::from_description(line) {
            total_area += gift.wrap_area();
            total_ribbon += gift.ribbon_length();
        }
    }

    Solution {
        one_star: Ok(total_area.to_string()),
        two_star: Ok(total_ribbon.to_string()),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn box_from_description() {
        let b = Box::from_description("2x3x4").unwrap();
        assert_eq!(b.length, 2);
        assert_eq!(b.width, 3);
        assert_eq!(b.height, 4);

        let b = Box::from_description("1x1x10").unwrap();
        assert_eq!(b.length, 1);
        assert_eq!(b.width, 1);
        assert_eq!(b.height, 10);

        let b = Box::from_description("1x2");
        assert!(b.is_none());
    }

    #[test]
    fn wrap_area() {
        let b = Box {
            length: 2,
            width: 3,
            height: 4,
        };
        assert_eq!(b.wrap_area(), 58);

        let b = Box {
            length: 1,
            width: 1,
            height: 10,
        };
        assert_eq!(b.wrap_area(), 43);
    }

    #[test]
    fn ribbon_length() {
        let b = Box {
            length: 2,
            width: 3,
            height: 4,
        };
        assert_eq!(b.ribbon_length(), 34);

        let b = Box {
            length: 1,
            width: 1,
            height: 10,
        };
        assert_eq!(b.ribbon_length(), 14);
    }
}
