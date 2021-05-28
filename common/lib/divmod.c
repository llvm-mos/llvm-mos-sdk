#ifndef __SLOW_DIV

// Relatively straigtforward implementation of long division in C. Not
// particularly tuned for performance, but clear.

unsigned long __udivsi3(unsigned long a, unsigned long b) {
  if (!b)
    return 0;

  unsigned long long divisor = b;
  divisor <<= 32;

  unsigned long q = 0;
  for (char i = 0; i < 32; ++i) {
    divisor >>= 1;

    q <<= 1;
    if (divisor <= a) {
      a -= divisor;
      q |= 1;
    }
  }

  return q;
}

unsigned long __umodsi3(unsigned long a, unsigned long b) {
  if (!b)
    return a;

  unsigned long long divisor = b;
  divisor <<= 32;

  for (char i = 0; i < 32; ++i) {
    divisor >>= 1;

    if (divisor <= a)
      a -= divisor;
  }

  return a;
}


#else  // __SLOW_DIV


// Very slow versions of the division algorithm. Still useful for validating
// whether or not breakages are likely to be caused by a miscompile of the
// division algorithm.

unsigned long __udivsi3(unsigned long a, unsigned long b) {
  unsigned long q = 0;
  while (a >= b) {
    a -= b;
    q++;
  }
  return q;
}

unsigned long __umodsi3(unsigned long a, unsigned long b) {
  while (a >= b)
    a -= b;
  return a;
}


#endif  // __SLOW_DIV
