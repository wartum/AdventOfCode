mod params;
mod input_provider;
mod solutions;

use input_provider::get_input;

type Error = Box<dyn std::error::Error>;
type Result<T> = std::result::Result<T, Error>;

#[tokio::main]
async fn main() -> Result<()>{
    let params = params::parse()?;
    let input = get_input(params.year, params.day, params.cache_input).await?;
    let solution = solutions::solve(params.year, params.day, input);

    match solution.one_star {
        Ok(answer) => println!("* : {}", answer),
        Err(err) => println!("* : FAILED! - {}", err),
    }
    match solution.two_star {
        Ok(answer) => println!("**: {}", answer),
        Err(err) => println!("**: FAILED! - {}", err),
    }

    Ok(())
}
