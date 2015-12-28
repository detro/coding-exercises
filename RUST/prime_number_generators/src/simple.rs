// Initial list of Known Primes taken from
// [wikipedia](https://en.wikipedia.org/wiki/Prime_number):
// why recalculate when we can use cut&paste?
const KNOWN_PRIMES_COUNT: usize = 168;
const KNOWN_PRIMES: [u64; KNOWN_PRIMES_COUNT] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997];

fn is_prime(candidate: &u64, found_primes: &Vec<u64>) -> bool {
  // No factor can be bigger than the square root of the given "candidate"
  let max_factor = (*candidate as f64).sqrt().floor() as u64;

  // Iterate over the KNOWN primes, stopping if/when "max_factor" is reached
  for prime in KNOWN_PRIMES.iter().skip(1).take_while(|&prime| *prime <= max_factor) {
    if candidate % prime == 0 {
      return false;
    }
  }

  // Iterate over the found primes, stopping if/when "max_factor" is reached
  for prime in found_primes.iter().take_while(|&prime| *prime <= max_factor) {
    if candidate % prime == 0 {
      return false;
    }
  }

  // If we are here, this number was not divisible by any previous prime and so it's a prime!
  return true;
}

/// Finds the n-th Prime using no special technique: just the basics
///
/// First, we have a list of "known" primes up to the 168th.
/// Second, we consider candidate for _primality_ only odd numbers.
/// Third, we try the modulo operation only using "known" of "found before" primes.
pub fn find(nth_prime: &usize) -> u64 {
  if *nth_prime <= KNOWN_PRIMES_COUNT {
    // If it's within the "known primes", just return the value
    return KNOWN_PRIMES[*nth_prime - 1];
  } else {
    let mut primes_count = KNOWN_PRIMES_COUNT;
    let mut primes: Vec<u64> = Vec::new();
    // Next prime candidate is the next odd number after biggest known prime
    let mut prime_candidate: u64 = KNOWN_PRIMES[KNOWN_PRIMES_COUNT - 1] + 2;

    // Keep going until we find the n-th prime
    while primes_count < *nth_prime {
      if is_prime(&prime_candidate, &primes) {
        // We found a new prime: store it and increase counter
        primes.push(prime_candidate);
        primes_count += 1;
      }

      // Next prime candidate (only odd numbers)
      prime_candidate += 2;
    }

    // Return the last prime found
    return *(primes.last().unwrap());
  }
}
