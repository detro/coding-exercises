var n = 1000;

function factorial(n) {
  var res = 1;
  for (var i = n; n >= 1; --n) {
    res *= n;
  }

  return res;
}

function factorialZeroTrail(n) {
  //
  // NOTE: This can't handle much after 20!
  //
  var nFact = factorial(n);
  var trailing = 0;

  while ((nFact % 10) == 0 && ++trailing) {
    nFact /= 10;
  }

  return trailing;
}

function factorialZeroTrail2(n) {
  //
  // NOTE: This is way better!
  //
  var factor = startFactor = 5;
  var trailing = 0;

  while (factor <= n) {
    trailing += Math.floor(n / factor);
    factor *= startFactor;
  }

  return trailing;
}

console.log("%d! = %d, %d!trailing = %d, %d!trailing2 = %d", n, factorial(n), n, factorialZeroTrail(n), n, factorialZeroTrail2(n));
