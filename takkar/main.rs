use std::io;

fn main() {
    let stdin = io::stdin();
    let mut s1 = String::new();
    let mut s2 = String::new();

    let _ = stdin.read_line(&mut s1);
    let _ = stdin.read_line(&mut s2);

    let a: i32 = s1.trim().parse().expect("Failed to parse s1 as i32");
    let b: i32 = s2.trim().parse().expect("Failed to parse s2 as i32");

    if a > b {
        println!("MAGA!");
    }
    else if a < b {
        println!("FAKE NEWS!");
    }
    else {
        println!("WORLD WAR 3!");
    }
}