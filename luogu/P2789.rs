use std::io::stdin;
use std::io::Read;
use std::collections::HashSet;

fn main() {
    let n = cin_i32();
    let mut f: Vec<HashSet<i32>> = vec![HashSet::new(); n as usize + 1];
    f[0].insert(0);
    for i in 1..=n {
        for a in 1..=i {
            let b = i - a;
            unsafe {
                let fb = &f[b as usize] as *const HashSet<i32>;
                let fi = &mut f[i as usize] as *mut HashSet<i32>;
                for x in (*fb).iter() {
                    (*fi).insert(a * b + x);
                }
            }
        }
    }
    println!("{}", f[n as usize].len());
}

#[allow(dead_code)]
fn getline() -> String {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    return line
        .chars()
        .filter(|&ch| ch != '\n' && ch != '\r')
        .collect();
}

fn getchar() -> Option<u8> {
    let mut buf = [0; 1];
    return match stdin().read_exact(&mut buf) {
        Ok(..) => Some(buf[0]),
        Err(..) => None // maybe meet EOF
    };
}

fn cin_i32() -> i32 {
    let mut x = 0;
    let mut f = 1;
    let mut ch = getchar();
    while !ch.unwrap().is_ascii_digit() {
        if ch.unwrap() == '-' as u8 {
            f = -1
        };
        ch = getchar();
    }
    while ch.is_some() && ch.unwrap().is_ascii_digit() {
        x = x * 10 + (ch.unwrap() as i32 - '0' as i32);
        ch = getchar();
    }
    return x * f;
}
