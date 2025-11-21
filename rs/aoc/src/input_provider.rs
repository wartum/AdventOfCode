use crate::Result;

pub async fn get_input(year: u32, day: u8) -> Result<String> {
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
