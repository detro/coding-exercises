extern crate stopwatch;
extern crate prime_number_generators;

use std::env;
use stopwatch::{Stopwatch};
use prime_number_generators::*;

const DEFAULT_N: usize = 1_000_000usize;

fn main() {
  let n: usize = env::args().skip(1).next()
        .and_then(|x| x.parse().ok())
        .unwrap_or(DEFAULT_N);

  println!("Calculating the #{} prime\n", n);

  let sw = Stopwatch::start_new();
  let nth_prime = simple::find(&n);
  println!("* Found prime {} using the 'simple' module and it took {}ms", nth_prime, sw.elapsed().as_millis());
}
