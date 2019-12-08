use std::io::*;
use std::io::prelude::*;

use std::fs::File;

use std::time::*;

fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).expect("Unknown error arrived");

    let startvalue: i32 = input.trim().parse().expect("Input isnt a valid number");
        
    let mut file = File::create("test.txt").expect("Reading file went wrong");

    for i in 0..(startvalue as f64 * 0.1) as i32 + 1 {
        let fileinput = format!("{}\n", i + startvalue);

        file.write(fileinput.as_bytes()).expect("Something went wrong");
    }
 
    
    //let mut filecontent = String::new();
    //filecontent = std::fs::read_to_string("test.txt").expect("Reading went wrong");

    //println!("{}", filecontent);
}
