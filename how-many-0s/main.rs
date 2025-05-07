use std::io::{self, BufRead};

fn cnt_zeros(bound: u64) -> u64 {
    let mut res = 0;
    let mut i = 1;

    loop {
        let l: u64 = bound / i; // left digits
        let r: u64 = bound % i; // right digits
        let a: u64 = l / 10; // left excl. rightmost digit
        let b: u64 = l % 10; // right excl. rightmost digit

        if a == 0 {
            break;
        }
        if b == 0 { // when the digit is zero itself
            res += (a - 1) * i + r + 1;
        }
        else {
            res += a * i; 
        }
        i *= 10;
    }
    res + 1 // +1 to account for zero itself
}

fn main() {
    let mut handle = io::stdin().lock();
    let mut line = String::new();

    loop {
        line.clear();
        let _ = handle.read_line(&mut line);
        line = line.trim().to_string();

        let mut parts = line.split_whitespace();
        let m = parts.next().unwrap();
        let n = parts.next().unwrap();

        if m == "-1" {
            break;
        }
        let m: u64 = m.parse().unwrap();
        let n: u64 = n.parse().unwrap();

        let cnt_m = if m > 0 { cnt_zeros(m - 1) } else { 0 };
        let cnt_n = cnt_zeros(n);
        println!("{}", cnt_n - cnt_m);
    }
}
