fn main() {
    println!("Hello, world!");
    
    let mut count = 1;
    loop {
        println!("This loop will run forever.");
        count = count + 1;
        if count > 5 {
            break;
        }
    }
}