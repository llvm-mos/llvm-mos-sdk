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

template <typename T> static inline T udivmod(T a, T b, T *rem) {
  if (!b || b > a) {
    *rem = a;
    return 0;
  }

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

  *rem = a;
  return q;
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
template <> struct make_unsigned<signed char> {
  typedef char type;
};
template <> struct make_unsigned<int> {
  typedef unsigned type;
};
template <> struct make_unsigned<long> {
  typedef unsigned long type;
};
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

template <typename T> static inline T divmod(T a, T b, T *rem) {
  typedef typename make_unsigned<T>::type UT;
  UT urem;
  T uq = static_cast<T>(udivmod(safe_abs(a), safe_abs(b), &urem));

  // Negating int_min here is fine, since it's only undefined behavior if the
  // signed division itself is.
  *rem = a < 0 ? -urem : urem;
  return (a < 0 != b < 0) ? -uq : uq;
}
