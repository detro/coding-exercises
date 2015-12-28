extern crate prime_number_generators;
use prime_number_generators::*;

#[test]
fn should_find_prime_simple() {
  let n = 100000;
  let nth_prime = simple::find(&n);
  let expected_nth_prime = 1299709;

  println!("The #{} prime number is: {}", n, nth_prime);
  assert_eq!(expected_nth_prime, nth_prime);
}
