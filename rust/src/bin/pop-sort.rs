fn main() {
    println!("Start pop sort");

    let mut vec: Vec<i32> = Vec::from([0, 9, 1, 6, 3, 2, 7, 8, 5, 4]);

    assert_eq!(vec.len(), 10);

    pop_sort(&mut vec);
}

fn pop_sort(array: &mut Vec<i32>) {
    for item in array {
        print!("{} ", item);
    }
    println!("\ndone");
}
