use crate::Result;

async fn get_online(year: u32, day: u8) -> Result<String> {
    let session = std::env::var("AOC_SESSION")?;
    let client = reqwest::Client::new();
    let url = format!("https://adventofcode.com/{}/day/{}/input", year, day);
    let rsp = client
        .get(&url)
        .header("Cookie", format!("session={}", session))
        .send()
        .await?
        .error_for_status()
        .map_err(|_| format!("Could not find input for given puzzle: {}/{}", year, day))?
        .text()
        .await?;
    Ok(rsp)
}

fn get_local(year: u32, day: u8) -> Option<String> {
    let path = format!("input{}{}.txt", year, day);
    std::fs::read_to_string(path).ok()
}

fn save_local(year: u32, day: u8, input: &str) {
    let path = format!("input{}{}.txt", year, day);
    let _ = std::fs::write(path, input);
}

pub async fn get_input(year: u32, day: u8, cache_input: bool) -> Result<String> {
    if let Some(input) = get_local(year, day) {
        return Ok(input);
    }

    match get_online(year, day).await {
        Ok(input) => {
            if cache_input {
                save_local(year, day, &input);
            }
            Ok(input)
        }
        Err(e) => Err(e),
    }
}
