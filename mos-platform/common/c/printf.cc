// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdio.h>

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "varint.h"

// Originally from the Public Domain C Library (PDCLib)

namespace {

struct Status {
  int base;       // base to which the value shall be converted
  uint16_t flags; // flags and length modifiers
  size_t n;       // print: maximum characters to be written
                  // scan:  number matched conversion specifiers
  size_t i;       // number of characters read/written
  char *s;        // *sprintf(): target buffer
                  // *sscanf():  source string
  size_t width;   // specified field width
  int prec;       // specified field precision
  va_list arg;    // argument stack
};

void put(char c, Status *status) {
  if (status->i < status->n) {
    if (status->s)
      status->s[status->i] = c;
    else
      putchar(c);
  }
  ++status->i;
}

#define E_minus (INT32_C(1) << 0)
#define E_plus (INT32_C(1) << 1)
#define E_alt (INT32_C(1) << 2)
#define E_space (INT32_C(1) << 3)
#define E_zero (INT32_C(1) << 4)

#define E_double (INT32_C(1) << 5)
#define E_ldouble (INT32_C(1) << 6)

#define E_lower (INT32_C(1) << 7)
#define E_unsigned (INT32_C(1) << 8)

#define E_exponent (INT32_C(1) << 9)
#define E_generic (INT32_C(1) << 10)

void print_string_padding(size_t prec, Status *status) {
  if (status->width <= prec)
    return;

  size_t padding = status->width - prec;
  while (padding--)
    put(' ', status);
}

void print_string(const char *s, Status *status) {
  size_t prec = status->prec < 0 ? SIZE_MAX : status->prec;
  for (size_t i = 0; i < prec; ++i) {
    if (s[i] == 0) {
      prec = i;
      break;
    }
  }

  if (!(status->flags & E_minus))
    print_string_padding(prec, status);

  while (prec-- > 0)
    put(*s++, status);

  if (status->flags & E_minus)
    print_string_padding(prec, status);
}

using namespace __impl;

// A variable-length unpaced BCD unsigned integer. Here decimal refers more to
// the "one byte per base" property; the base isn't necessarily ten. Note that
// size is mutable, unlike binary varints. (Binary varints typically wrap real
// language types with known fixed sizes.)
class BcdVarInt {
public:
#if _PRINTF_FLOAT
  typedef size_t Size;
#else
  typedef char Size;
#endif

private:
  char base;
  Size size_;

public:
  BcdVarInt(const BcdVarInt &other) = delete;

  char *bytes() { return (char *)&size_ + sizeof(size_); };
  const char *bytes() const { return (const char *)&size_ + sizeof(size_); };

  Size size() const { return size_; }

  BcdVarInt &operator++();

  void mul2();
  void mul5_in_base_10();
  void div_pow_base(Size pow);

protected:
  BcdVarInt(char base) : size_(0), base(base) {}
};

BcdVarInt &BcdVarInt::operator++() {
  for (Size i = 0; i < size_; i++) {
    ++bytes()[i];
    if (bytes()[i] < base)
      return *this;
    bytes()[i] -= base;
  }
  bytes()[size_++] = 1;
  return *this;
}

void BcdVarInt::mul2() {
  bool carry = false;
  for (Size i = 0; i < size_; i++) {
    bytes()[i] *= 2;
    if (carry)
      ++bytes()[i];
    carry = bytes()[i] >= base;
    if (carry)
      bytes()[i] -= base;
  }
  if (carry)
    bytes()[size_++] = 1;
}

// Multiply by 5; only works in base 10.
void BcdVarInt::mul5_in_base_10() {
  char carry = 0;
  for (Size i = 0; i < size_; i++) {
    // The carry increases once every two input values: 0 5 10 15 ...
    char new_carry = bytes()[i] / 2;
    // Odd * 5 has 5 as its lower digit; even * 5, 0.
    bytes()[i] = bytes()[i] % 2 ? 5 : 0;
    bytes()[i] += carry;
    // The low byte is at most 5, and the max carry is (9 * 5)/10 = 4, so it can
    // never overflow into a new carry.
    carry = new_carry;
  }
  if (carry)
    bytes()[size_++] = carry;
}

// Divide by a power of the base.
void BcdVarInt::div_pow_base(Size pow) {
  size_ -= pow;
  for (Size i = 0; i < size_; i++)
    bytes()[i] = bytes()[i + pow];
}

template <BcdVarInt::Size Capacity> class BcdBigInt : public BcdVarInt {
  char space[Capacity];

public:
  BcdBigInt(char base) : BcdVarInt(base) {}
};

void int_to_bcd(VarInt &value, BcdVarInt &bcd) {
  // TODO: Describe double dabble.
  for (char i = 0; i < value.size() * 8; i++) {
    bcd.mul2();
    if (value.high_bit())
      ++bcd;
    value.shl();
  }
}

char bcd_to_char(char bcd, bool lower) {
  if (bcd <= 9)
    return '0' + bcd;
  return (lower ? 'a' : 'A') + (bcd - 10);
}

void print_bcd_int(BcdVarInt &value, bool negative, Status *status) {
  size_t prec = status->prec < 0 ? 1 : status->prec;
  if (status->flags & E_alt && status->base == 8 && prec < value.size() + 1)
    prec = value.size() + 1;

  // A prefix string: empty, "0x", or the sign/space.
  char prefix[2];
  char prefix_width = 0;

  if (status->flags & E_alt && status->base == 16 && value.size()) {
    prefix[0] = '0';
    prefix[1] = status->flags & E_lower ? 'x' : 'X';
    prefix_width = 2;
  } else {
    if (negative) {
      prefix[0] = '-';
      ++prefix_width;
    } else if (status->flags & E_plus) {
      prefix[0] = '+';
      ++prefix_width;
    } else if (status->flags & E_space) {
      prefix[0] = ' ';
      ++prefix_width;
    }
  }

  size_t width = prec;
  if (width < value.size())
    width = value.size();
  width += prefix_width;
  size_t padding = (status->width > width) ? status->width - width : 0;

  if (!(status->flags & (E_minus | E_zero)))
    for (; padding; --padding)
      put(' ', status);

  if (prefix_width)
    put(prefix[0], status);
  if (prefix_width == 2)
    put(prefix[1], status);

  if (status->flags & E_zero && !(status->flags & E_minus))
    for (; padding; --padding)
      put('0', status);

  while (prec-- > value.size())
    put('0', status);

  if (value.size()) {
    for (char i = value.size() - 1; i != 0; i--)
      put(bcd_to_char(value.bytes()[i], status->flags & E_lower), status);
    put(bcd_to_char(value.bytes()[0], status->flags & E_lower), status);
  }

  if (status->flags & E_minus)
    for (; padding; --padding)
      put(' ', status);
}

void print_int(VarInt &value, bool negative, Status *status) {
  BcdBigInt<sizeof("18446744073709551615")> bcd(status->base);
  int_to_bcd(value, bcd);
  print_bcd_int(bcd, negative, status);
}

#ifdef _PRINTF_FLOAT
void print_double(double value, Status *status) {
  size_t prec;
  if (status->prec < 0)
    prec = status->base == 16 ? 52 / 4 : 6;
  else
    prec = status->prec;

  union DoubleRepr {
    double val;
    struct {
      unsigned long long mant : 52;
      unsigned exp : 11;
      bool sign : 1;
    } repr;
  } val_repr;
  val_repr.val = value;

  // Infinity or NaN
  if (val_repr.repr.exp == 0x7ff) {
    char str[5]; // Max: -inf
    str[0] = '\0';
    if (val_repr.repr.sign)
      strcat(str, "-");
    else if (status->flags & E_plus)
      strcat(str, "+");
    else if (status->flags & E_space)
      strcat(str, " ");
    strcat(str, val_repr.repr.mant == 0 ? "inf" : "nan");
    if (!(status->flags & E_lower))
      for (char *s = str; *s; s++)
        *s = toupper(*s);
    print_string(str, status);
    return;
  }

  // Start by normalizing the mantissa to an unsigned integer and exponent
  // pair, mant and exp, such that value = mant * 2^exp.
  unsigned long long mant;
  int exp;
  if (val_repr.repr.mant == 0 && val_repr.repr.exp == 0) {
    mant = exp = 0;
  } else {
    mant = val_repr.repr.mant | (1ull << 52);
    // Move the decimal point all the way to the right of mantissa by sucking
    // 2^52 out of the exponent.
    exp = val_repr.repr.exp - 1023 - 52;
  }

  // Next, convert to another integer pair, mant_b and exp_b, such that
  // mant_b * b^exp_b = mant * 2^exp.

  // For base 16, the actual value of b is 2; that's what we report. So exp_b =
  // exp, and mant_b = mant; there's nothing to do.

  // If exp >= 0, then 2^exp >= 1, so we can naturally take exp_b = 0 and
  // mant_b = mant * 2^exp. This works regardless of the base.

  // Otherwise, if b=10, multiply and divide by 5^exp to create a factor of
  // 10^exp: mant * 2^exp = mant * 2^exp * 5^exp * 5^-exp = mant * 5^-exp *
  // 10^exp.  We can thus take exp_b = exp and mant_b = mant * 5^-exp.

  // Otherwise, if b=16, then take mant_b = mant * 2^k and exp_b = (exp-k)/4,
  // where k is the smallest nonnegative integer such that exp_b is an integer.
  // Then mant_b * 16^exp_b = mant * 2^k * 16^((exp-k)/4) = mant *  2^(k +
  // 4(exp-k)/4) = mant * 2^exp

  // Computing mant_b requires arbitrary precision arithmetic. This could be
  // most efficiently done in base 2, but the next step is to convert it to an
  // arbitrary precision BCD number, so we may as well do it in BCD, since
  // multiplying by both 2 and 5 (in base 10) is still easy in BCD.

  // How many digits are required to store mant_b?

  // If the exponent >= 0, then log10(mant_b) = log10(mant * 2^exp) =
  // log10(mant) + log10(2^exp) < log10(2^52) + log10(2^(1023-52)) =
  // log2(2^52)/log2(10) + log2(2^971)/log2(10) = 52/log2(10) + 971/log2(10) <
  // 308.

  // If the exponent < 0, then log10(mant_b) = log10(mant * 5^-exp) =
  // log10(mant) + log10(5^-exp) < log10(2^52) + log10(5^(-(-1022-52)) =
  // log10(2^52) + log10(5^1074) = log2(2^52)/log2(10) + log5(5^1074)/log5(10) =
  // 52/log2(10) + 1074/log5(10) < 767.

  // The b=16 case only requires up to 3 doublings of a 64-bit mantissa; it's
  // never large enough to limit.

  BcdBigInt<767> bcd(status->base);
  // Double-dabble mant into BCD.
  for (char i = 0; i < 64; ++i) {
    bcd.mul2();
    if (mant & (1ull << 63))
      ++bcd;
    mant <<= 1;
  }

  int exp_b;
  size_t ones_idx;
  if (status->base == 16) {
    exp_b = exp;
  } else {
    if (exp >= 0) {
      exp_b = 0;
      // mant_b *= 2^exp.
      while (exp--)
        bcd.mul2();
    } else {
      if (status->base == 10) {
        exp_b = exp;
        // mant_b *= 5^-exp;
        while (exp++)
          bcd.mul5_in_base_10();
      } else {
        while (exp & 0b11) {
          bcd.mul2();
          --exp;
        }
        exp_b = exp >> 2;
      }
    }
    ones_idx = -exp_b;
  }

  if (status->flags & (E_exponent | E_generic)) {
    if (bcd.size()) {
      // In exponential form, the highest digit is always the one's place.
      size_t shift = bcd.size() - 1;
      if (status->base == 16)
        shift *= 4;
      exp_b += shift;
    } else {
      // If the value is zero, the exponent is zero.
      exp_b = 0;
    }
  }

  if (status->flags & E_generic) {
    // Compute P from standard.
    int p = prec;
    if (!p)
      p = 1;

    // Test from the standard.
    if (p > exp_b && exp_b >= -4) {
      prec = p - (exp_b + 1);
    } else {
      prec = p - 1;
      status->flags |= E_exponent;
    }
  }

  BcdBigInt<4> exp_bcd(/*base=*/10);
  bool exp_neg;

  if (status->flags & E_exponent) {
    ones_idx = bcd.size() ? bcd.size() - 1 : 0;
    exp_neg = exp_b < 0;
    size_t uexp = exp_neg ? -exp_b : exp_b;
    for (char i = 0; i < 16; i++) {
      exp_bcd.mul2();
      if (uexp & (1 << 15))
        ++exp_bcd;
      uexp <<= 1;
    }
  }

  long low_idx = (long)ones_idx - prec;
  long rounding_idx = low_idx - 1;

  // If the digit to use to round is within the BCD, then it has a value that
  // needs to be folded into the lowest digit to print.
  if (0 <= rounding_idx && rounding_idx < bcd.size()) {
    char rounding_digit = bcd.bytes()[rounding_idx];

    bcd.div_pow_base(low_idx);
    ones_idx = prec;
    low_idx = 0;
    char low_digit;
    low_digit = bcd.size() == 0 ? 0 : bcd.bytes()[0];
    if (rounding_digit == 5 ? low_digit % 2 != 0 : rounding_digit > 5)
      ++bcd;
  }

  // Lower the precision to remove trailing zeros.
  if ((status->base == 16 && status->prec < 0) ||
      (status->flags & E_generic && !(status->flags & E_alt))) {
    for (; low_idx < 0; ++low_idx)
      --prec;
    for (; prec > 0 && bcd.bytes()[low_idx] == 0; ++low_idx)
      --prec;
  }

  bool has_period = prec || status->flags & E_alt;

  size_t sign_width =
      val_repr.repr.sign || status->flags & (E_plus | E_space) ? 1 : 0;
  size_t prefix_width = status->base == 16 ? 2 : 0;
  size_t whole_width = ones_idx < bcd.size() ? bcd.size() - ones_idx : 1;
  size_t dot_width = has_period ? 1 : 0;
  size_t frac_width = prec;
  size_t exp_width = 0;
  if (status->flags & E_exponent) {
    exp_width = status->base == 16 ? 1 : 2;
    if (exp_bcd.size() > exp_width)
      exp_width = exp_bcd.size();
    exp_width += 2; // exponent letter and sign
  }

  size_t width = sign_width + prefix_width + whole_width + dot_width +
                 frac_width + exp_width;
  size_t padding = 0;
  if (status->width > width)
    padding = status->width - width;

  if (!(status->flags & (E_zero | E_minus)))
    while (padding--)
      put(' ', status);

  if (val_repr.repr.sign)
    put('-', status);
  else if (status->flags & E_plus)
    put('+', status);
  else if (status->flags & E_space)
    put(' ', status);

  if (status->base == 16) {
    put('0', status);
    put(status->flags & E_lower ? 'x' : 'X', status);
  }

  if (status->flags & E_zero)
    while (padding--)
      put('0', status);

  // Print the whole part of the number
  if (ones_idx < bcd.size()) {
    // ones_idx may be zero.
    for (BcdVarInt::Size i = bcd.size() - 1; i > ones_idx; --i) {
      put(bcd_to_char(bcd.bytes()[i], status), status);
    }
    put(bcd_to_char(bcd.bytes()[ones_idx], status), status);
  } else {
    put('0', status);
  }

  if (has_period)
    put('.', status);

  // Print the fractional part of the number.
  for (int i = (int)ones_idx - 1; prec--; --i) {
    if (i >= 0 && i < bcd.size()) {
      put(bcd_to_char(bcd.bytes()[i], status), status);
    } else {
      put('0', status);
    }
  }

  if (status->flags & E_exponent) {
    if (status->base == 16)
      put(status->flags & E_lower ? 'p' : 'P', status);
    else
      put(status->flags & E_lower ? 'e' : 'E', status);
    put(exp_neg ? '-' : '+', status);
    for (char i = status->base == 16 ? 1 : 2; i > exp_bcd.size(); --i)
      put('0', status);
    if (exp_bcd.size()) {
      for (char i = exp_bcd.size() - 1; i > 0; --i)
        put('0' + exp_bcd.bytes()[i], status);
      put('0' + exp_bcd.bytes()[0], status);
    }
  }

  if (status->flags & E_minus)
    while (padding--)
      put(' ', status);
}

#ifdef _PRINTF_LONG_DOUBLE
void print_ldouble(long double value, Status *status) {
  print_double(value, status);
}
#endif

#endif

unsigned simple_strtoui(const char *__restrict__ nptr,
                        char **__restrict endptr) {
  unsigned result = 0;

  for (*endptr = (char *)nptr; **endptr && '0' <= **endptr && **endptr <= '9';
       ++*endptr) {
    result *= 10;
    result += **endptr - '0';
  }

  return result;
}

const char *print(const char *spec, Status *status) {
  const char *orig_spec = spec;

  if (*(++spec) == '%') {
    /* %% -> print single '%' */
    put(*spec, status);
    return ++spec;
  }

  /* Initializing status structure */
  status->flags = 0;
  status->base = 0;
  status->width = 0;
  status->prec = -1;

  /* First come 0..n flags */
  for (;;) {
    switch (*spec) {
    case '-':
      /* left-aligned output */
      status->flags |= E_minus;
      ++spec;
      break;

    case '+':
      /* positive numbers prefixed with '+' */
      status->flags |= E_plus;
      ++spec;
      break;

    case '#':
      /* alternative format (leading 0x for hex, 0 for octal) */
      status->flags |= E_alt;
      ++spec;
      break;

    case ' ':
      /* positive numbers prefixed with ' ' */
      status->flags |= E_space;
      ++spec;
      break;

    case '0':
      /* right-aligned padding done with '0' instead of ' ' */
      status->flags |= E_zero;
      ++spec;
      break;

    default:
      /* not a flag, exit flag parsing */
      goto flags_done;
    }
  }
flags_done:;

  /* Optional field width */
  if (*spec == '*') {
    /* Retrieve width value from argument stack */
    int width = va_arg(status->arg, int);

    if (width < 0) {
      status->flags |= E_minus;
      status->width = abs(width);
    } else {
      status->width = width;
    }

    ++spec;
  } else {
    // If a width is given, simple_strtoui() will return its value. If not
    // given, simple_strtoui() will return zero. In both cases, endptr will
    // point to the rest of the conversion specifier - just what we need.
    status->width = simple_strtoui(spec, (char **)&spec);
  }

  /* Optional precision */
  if (*spec == '.') {
    ++spec;

    if (*spec == '*') {
      // Retrieve precision value from argument stack. A negative value is as if
      // no precision is given - as precision is initalized to -1.
      status->prec = va_arg(status->arg, int);
      ++spec;
    } else {
      char *endptr;
      status->prec = simple_strtoui(spec, &endptr);

      if (spec == endptr) {
        /* Decimal point but no number - equals zero */
        status->prec = 0;
      }

      spec = endptr;
    }

    /* Having a precision cancels out any zero flag. */
    status->flags &= ~E_zero;
  }

  // Optional length modifier We step one character ahead in any case, and step
  // back only if we find there has been no length modifier (or step ahead
  // another character if it has been "hh" or "ll").
  char dst_size = sizeof(int); // Logical size of argument in bytes.
  char src_size = sizeof(int); // Actual size of argument in bytes.
  switch (*spec++) {
  case 'h':
    if (*spec == 'h') {
      /* hh -> char */
      dst_size = sizeof(char);
      src_size = sizeof(int);
      ++spec;
    } else {
      /* h -> short */
      dst_size = sizeof(short);
      src_size = sizeof(int);
    }
    break;

  case 'l':
    if (*spec == 'l') {
      /* ll -> long long */
      dst_size = sizeof(long long);
      src_size = sizeof(long long);
      ++spec;
    } else {
      /* k -> long */
      dst_size = sizeof(long);
      src_size = sizeof(long);
    }
    break;

  case 'j':
    /* j -> intmax_t, which might or might not be long long */
    dst_size = sizeof(intmax_t);
    src_size = sizeof(intmax_t);
    break;

  case 'z':
    /* z -> size_t, which might or might not be unsigned int */
    dst_size = sizeof(size_t);
    src_size = sizeof(size_t);
    break;

  case 't':
    /* t -> ptrdiff_t, which might or might not be long */
    dst_size = sizeof(ptrdiff_t);
    src_size = sizeof(ptrdiff_t);
    break;

#ifdef _PRINTF_LONG_DOUBLE
  case 'L':
    /* L -> long double */
    status->flags |= E_ldouble;
    break;
#endif // _PRINTF_LONG_DOUBLE

  default:
    --spec;
    break;
  }

  /* Conversion specifier */
  switch (*spec) {
  case 'd':
    /* FALLTHROUGH */

  case 'i':
    status->base = 10;
    break;

  case 'o':
    status->base = 8;
    status->flags |= E_unsigned;
    break;

  case 'u':
    status->base = 10;
    status->flags |= E_unsigned;
    break;

  case 'x':
    status->base = 16;
    status->flags |= (E_lower | E_unsigned);
    break;

  case 'X':
    status->base = 16;
    status->flags |= E_unsigned;
    break;

#ifdef _PRINTF_FLOAT
  case 'f':
    status->base = 10;
    status->flags |= (E_double | E_lower);
    break;

  case 'F':
    status->base = 10;
    status->flags |= (E_double);
    break;

  case 'e':
    status->base = 10;
    status->flags |= (E_exponent | E_double | E_lower);
    break;

  case 'E':
    status->base = 10;
    status->flags |= (E_exponent | E_double);
    break;

  case 'g':
    status->base = 10;
    status->flags |= (E_generic | E_double | E_lower);
    break;

  case 'G':
    status->base = 10;
    status->flags |= (E_generic | E_double);
    break;

  case 'a':
    status->base = 16;
    status->flags |= (E_exponent | E_double | E_lower);
    break;

  case 'A':
    status->base = 16;
    status->flags |= (E_exponent | E_double);
    break;
#endif // _PRINTF_FLOAT

  case 'c': {
    /* TODO: wide chars. */
    char c_str[2];
    c_str[0] = (char)va_arg(status->arg, int);
    c_str[1] = '\0';
    print_string(c_str, status);
    return ++spec;
  }

  case 's':
    /* TODO: wide chars. */
    print_string(va_arg(status->arg, char *), status);
    return ++spec;

  case 'p':
    status->base = 16;
    status->flags |= (E_lower | E_unsigned | E_alt);
    break;

  case 'n': {
    int *val = va_arg(status->arg, int *);
    *val = status->i;
    return ++spec;
  }

  default:
    /* No conversion specifier. Bad conversion. */
    return orig_spec;
  }

  /* Do the actual output based on our findings */
  if (status->base != 0) {
#ifdef _PRINTF_FLOAT
    /* TODO: Check for invalid flag combinations. */
    if (status->flags & E_double) {
#ifdef _PRINTF_LONG_DOUBLE
      /* Floating Point conversions */
      if (status->flags & E_ldouble) {
        long double value = va_arg(status->arg, long double);
        print_ldouble(value, status);
      } else
#endif // _PRINTF_LONG_DOUBLE
      {
        double value = va_arg(status->arg, double);
        print_double(value, status);
      }
    } else
#endif // _PRINTF_FLOAT
    {
      char space[sizeof(BigInt<sizeof(long long)>)];

      VarInt &value = VarInt::make(space, dst_size);
      memcpy(value.bytes(), status->arg, value.size());
      status->arg = (char *)status->arg + src_size;

      bool negative = !(status->flags & E_unsigned) && value.negative();
      if (negative)
        value.negate();
      print_int(value, negative, status);
    }

#if 0
    if (status->flags & E_minus) {
      /* Left-aligned filling */
      while (status->current < status->width) {
        put(' ', status);
        ++(status->current);
      }
    }
#endif

    if (status->i >= status->n && status->n > 0)
      status->s[status->n - 1] = '\0';
  }

  return ++spec;
}

} // namespace

extern "C" {

__attribute__((weak)) int fprintf(FILE *__restrict__ stream,
                                  const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vfprintf(stream, format, ap);
  va_end(ap);
  return rc;
}

__attribute__((weak)) int printf(const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vfprintf(stdout, format, ap);
  va_end(ap);
  return rc;
}

__attribute__((weak)) int snprintf(char *__restrict__ s, size_t n,
                                   const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vsnprintf(s, n, format, ap);
  va_end(ap);
  return rc;
}

__attribute__((weak)) int sprintf(char *__restrict__ s,
                                  const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vsnprintf(s, SIZE_MAX, format, ap);
  va_end(ap);
  return rc;
}

__attribute__((weak)) int vfprintf(FILE *__restrict__ stream,
                                   const char *__restrict__ format,
                                   va_list arg) {
  /* TODO: This function should interpret format as multibyte characters.  */
  Status status;
  status.n = SIZE_MAX;
  status.i = 0;
  status.s = NULL;

  va_copy(status.arg, arg);

  while (*format != '\0') {
    const char *rc;

    if ((*format != '%') || ((rc = print(format, &status)) == format)) {
      /* No conversion specifier, print verbatim */
      putchar(*format);
      ++format;
      status.i++;
    } else {
      /* Continue parsing after conversion specifier */
      format = rc;
    }
  }

  va_end(status.arg);
  return status.i;
}

__attribute__((weak)) int vprintf(const char *__restrict__ format,
                                  va_list arg) {
  return vfprintf(stdout, format, arg);
}

__attribute__((weak)) int vsnprintf(char *__restrict__ s, size_t n,
                                    const char *__restrict__ format,
                                    va_list arg) {
  /* TODO: This function should interpret format as multibyte characters.  */
  Status status;
  status.n = n;
  status.i = 0;
  status.s = s;

  va_copy(status.arg, arg);

  while (*format != '\0') {
    const char *rc;

    if ((*format != '%') || ((rc = print(format, &status)) == format)) {
      /* No conversion specifier, print verbatim */
      if (status.i < n)
        s[status.i] = *format;

      status.i++;
      format++;
    } else {
      /* Continue parsing after conversion specifier */
      format = rc;
    }
  }

  if (status.i < n) {
    s[status.i] = '\0';
  }

  va_end(status.arg);
  return status.i;
}

__attribute__((weak)) int
vsprintf(char *__restrict__ s, const char *__restrict__ format, va_list arg) {
  return vsnprintf(s, SIZE_MAX, format, arg);
}

} // extern "C"
