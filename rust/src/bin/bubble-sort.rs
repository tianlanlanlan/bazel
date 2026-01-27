fn main() {
    println!("Start pop sort");

    let mut vec: Vec<i32> = Vec::from([0, 9, 1, 6, 3, 2, 7, 8, 5, 4]);

    assert_eq!(vec.len(), 10);

    bubble_sort(&mut vec);
}

// 升序排序
fn bubble_sort(array: &mut Vec<i32>) {
    let n = array.len();

    for offet in 1..n {
        let end = n - offet;
        for i in 0..end {
            if array[i] > array[i + 1] {
                array.swap(i, i + 1);
            }
        }
    }

    for item in array {
        print!("{} ", item);
    }
    println!("")
}
