extern crate stopwatch;
extern crate prime_number_generators;

use std::env;
use stopwatch::{Stopwatch};
use prime_number_generators::*;

const DEFAULT_N: usize = 1_000_000usize;

fn main() {
  let n = match env::args().skip(1).next() {
    Some(x) => match x.parse::<usize>() {
      Ok(y) => y,
      Err(_) => DEFAULT_N
    },
    None => DEFAULT_N
  };

  println!("Calculating the #{} prime\n", n);

  let sw = Stopwatch::start_new();
  let nth_prime = simple::find(&n);
  println!("* Found prime {} using the 'simple' module and it took {}ms", nth_prime, sw.elapsed().num_milliseconds());
}
