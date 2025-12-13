fn main() {
    println!("Hello, world!");

    let mut count = 1;
    loop {
        count = count + 1;
        println!("Loop count: {}", count);
        if count > 5 {
            break;
        }
    }

    {
        let count = 100;
        println!("Inner block count starts at: {}", count);
    }

    println!("Final count after loop: {}", count);

    let spaces = "abc";
    let spaces = spaces.len();
    println!("Length of spaces: {}", spaces);
}
