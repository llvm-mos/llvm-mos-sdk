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

template <typename T> struct make_unsigned;
template <> struct make_unsigned<signed char> { typedef char type; };
template <> struct make_unsigned<int> { typedef unsigned type; };
template <> struct make_unsigned<long> { typedef unsigned long type; };
template <> struct make_unsigned<long long> {
  typedef unsigned long long type;
};

// Version of abs that returns INT_MIN for INT_MIN, without undefined behavior.
template <typename T>
static inline typename make_unsigned<T>::type safe_abs(T a) {
  typedef typename make_unsigned<T>::type UT;
  UT int_min = static_cast<UT>(1) << sizeof(UT) * 8 - 1;
  UT ua = static_cast<UT>(a);
  return (a >= 0 || ua == int_min) ? ua : static_cast<UT>(-a);
}

template <typename T> static inline T div(T a, T b) {
  typedef typename make_unsigned<T>::type UT;
  T u = static_cast<T>(safe_abs(a) / safe_abs(b));
  // Negating int_min here is fine, since it's only undefined behavior if the
  // signed division itself is.
  return (a < 0 != b < 0) ? -u : u;
}

template <typename T> static inline T mod(T a, T b) {
  typedef typename make_unsigned<T>::type UT;
  T u = static_cast<T>(safe_abs(a) % safe_abs(b));
  // Negating int_min here is fine, since it's only undefined behavior if the
  // signed mod itself is.
  return a < 0 ? -u : u;
}

extern "C" {
char __udivqi3(char a, char b) { return udiv(a, b); }
unsigned __udivhi3(unsigned a, unsigned b) { return udiv(a, b); }
unsigned long __udivsi3(unsigned long a, unsigned long b) { return udiv(a, b); }
unsigned long long __udivdi3(unsigned long long a, unsigned long long b) {
  return udiv(a, b);
}

char __umodqi3(char a, char b) { return umod(a, b); }
unsigned __umodhi3(unsigned a, unsigned b) { return umod(a, b); }
unsigned long __umodsi3(unsigned long a, unsigned long b) { return umod(a, b); }
unsigned long long __umoddi3(unsigned long long a, unsigned long long b) {
  return umod(a, b);
}

signed char __divqi3(signed char a, signed char b) { return div(a, b); }
int __divhi3(int a, int b) { return div(a, b); }
long __divsi3(long a, long b) { return div(a, b); }
long long __divdi3(long long a, long long b) { return div(a, b); }

signed char __modqi3(signed char a, signed char b) { return mod(a, b); }
int __modhi3(int a, int b) { return mod(a, b); }
long __modsi3(long a, long b) { return mod(a, b); }
long long __moddi3(long long a, long long b) { return mod(a, b); }
}
