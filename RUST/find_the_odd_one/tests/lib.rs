extern crate find_odd_one;
use find_odd_one::*;

fn generate_input() -> Vec<i32> {
  return vec![1, 2, 3, 6, 1, 4, 3, 2, 4, 1, 7, 2, 3, 2, 6, 3, 1, 4, 1, 7, 4, 1, 6];
}

#[test]
fn should_find_odd_one_using_xor() {
  let input = generate_input();
  assert_eq!(6, find_odd_one_using_xor(input));
}

#[test]
fn should_find_odd_one_using_set() {
  assert_eq!(6, find_odd_one_using_set(generate_input()));
}