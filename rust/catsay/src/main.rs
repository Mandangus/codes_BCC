extern crate colored;
extern crate structopt;
use structopt::StructOpt;
use colored::*;
#[derive(StructOpt)]
struct Options{
    #[structopt(default_value = "Peck!")]
    /// What does the pingu say?
    message: String,
    #[structopt(short = "d", long = "dead")]
    /// Oh no! Pingu died :(
    dead: bool,
}

fn main() {
    let options = Options::from_args();
    let eye = if options.dead {"x"} else {"0"};
    let message = options.message;
    println!("{}", message.bright_yellow().underline());
    println!("   \\");
    println!("    \\");
    println!("        .--.");
    println!("       |{eye}_{eye} |",eye=eye.bright_red());
    println!("       |:_/ |");
    println!("      //   \\ \\");
    println!("     (|     | )");
    println!("    /'\\_   _/`\\");
    println!("    \\___)=(___/");
}
