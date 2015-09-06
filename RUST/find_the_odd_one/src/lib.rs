use std::collections::HashSet;

/// Uses XOR operator to find the integer that appears an odd number of times.
///
/// It works as long as there is only one integer that appears an odd number
/// of times.
pub fn find_odd_one_using_xor(input: Vec<i32>) -> i32 {
  let mut odd_one = 0;

  for i in input {
    odd_one ^= i;
  }

  return odd_one;
}

/// Uses a Set (an HashSet) to track the odd/even times presence of numbers.
///
/// The ides is to add an element if absent, and remove it if present.
/// Given the simmetry of the operation, if a nummber appear an odd number of
/// times, it will left alone in the Set.
pub fn find_odd_one_using_set(input: Vec<i32>) -> i32 {
  let mut seen = HashSet::new();

  for i in input {
    if !seen.contains(&i) {
      seen.insert(i);
    } else {
      seen.remove(&i);
    }
  }

  return *(seen.iter().next().unwrap());
}