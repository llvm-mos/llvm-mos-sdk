#ifndef __SLOW_DIV

// Relatively straigtforward implementation of long division in C. Not
// particularly tuned for performance, but clear.

template <typename T> static inline T udiv(T a, T b) {
  if (!b || b > a)
    return 0;

  // Here b <= a.

  // Shift b as far left as possible without exceeding a. If the hightest bit of
  // b is 1, then the next shift, if were performed at a higher bit width, would
  // make it exceed a.
  char num_digits_remaining = 0;
  while (!(b & static_cast<T>(1) << (sizeof(T) * 8 - 1)) && (b << 1) <= a) {
    b <<= 1;
    ++num_digits_remaining;
  }

  // Since b <= a, the first digit is always 1. This is not counted in
  // num_digits_remaining.
  T q = 1;
  a -= b;
  b >>= 1;

  for (; num_digits_remaining; --num_digits_remaining) {
    // Prepare q to receive the next digit as its LSB.
    q <<= 1;

    // If the quotient digit is a 1
    if (b <= a) {
      q |= 1;

      // Subtract out 1 * the divisor.
      a -= b;
    }

    // The next quotient digit corrsponds to one smaller power of 2 times the
    // divisor.
    b >>= 1;
  }

  return q;
}

template <typename T> static inline T umod(T a, T b) {
  if (!b || b > a)
    return a;

  // Here b <= a.

  // Shift b as far left as possible without exceeding a. If the hightest bit of
  // b is 1, then the next shift, if were performed at a higher bit width, would
  // make it exceed a.
  char num_digits_remaining = 0;
  while (!(b & static_cast<T>(1) << (sizeof(T) * 8 - 1)) && (b << 1) <= a) {
    b <<= 1;
    ++num_digits_remaining;
  }

  // Since b <= a, the first digit is always 1. This is not counted in
  // num_digits_remaining.
  a -= b;
  b >>= 1;

  for (; num_digits_remaining; --num_digits_remaining) {
    // If the quotient digit is a 1
    if (b <= a) {
      // Subtract out 1 * the divisor.
      a -= b;
    }

    // The next quotient digit corrsponds to one smaller power of 2 times the
    // divisor.
    b >>= 1;
  }

  return a;
}

#else // __SLOW_DIV

// Very slow versions of the division algorithm. Still useful for validating
// whether or not breakages are likely to be caused by a miscompile of the
// division algorithm.

template <typename T> static inline T udiv(T a, T b) {
  T q = 0;
  while (a >= b) {
    a -= b;
    q++;
  }
  return q;
}

template <typename T> static inline T umod(T a, T b) {
  while (a >= b)
    a -= b;
  return a;
}

#endif // __SLOW_DIV

extern "C" {
unsigned long __udivqi3(char a, char b) { return udiv(a, b); }
unsigned long __udivhi3(unsigned a, unsigned b) { return udiv(a, b); }
unsigned long __udivsi3(unsigned long a, unsigned long b) { return udiv(a, b); }
unsigned long __udivdi3(unsigned long long a, unsigned long long b) { return udiv(a, b); }

char __umodqi3(char a, char b) { return umod(a, b); }
unsigned __umodhi3(unsigned a, unsigned b) { return umod(a, b); }
unsigned long __umodsi3(unsigned long a, unsigned long b) { return umod(a, b); }
unsigned long long __umoddi3(unsigned long long a, unsigned long long b) { return umod(a, b); }
}
