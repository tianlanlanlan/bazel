fn main() {
    let a = 10;
    println!("Hello, world!");
    println!("a = {}", a);

    let mut vec = Vec::new();
    vec.push(1);
    vec.push(2);
    vec.push(3);
    for item in vec {
        println!("{}", item);
    }
}
