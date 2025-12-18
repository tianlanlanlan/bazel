use std::collections::HashMap;

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

    // Test hashmap
    let mut book_reviews = HashMap::new();
    book_reviews.insert("Hello".to_string(), "World".to_string());

    for (book, review) in &book_reviews {
        println!("{} {}", book, review);
    }
}
