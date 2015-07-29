use std::env;

fn main() {
    let input = env::args().skip(1).map(|i| i.parse::<u32>());
    let mut odd_one = 0;

    print!("Input array is: [\n  ");
    for i in input {
        let curr = i.unwrap();
        print!("{} ", curr);
        odd_one ^= curr;
    }
    print!("\n]\n");

    print!("Using XOX, the odd one is: {}\n", odd_one);
}
