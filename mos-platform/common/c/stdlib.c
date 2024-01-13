// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdlib.h>

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Originally from the Public Domain C Library (PDCLib).

static bool is_hex_digit(char c) {
  return isdigit(c) || 'a' <= c && c <= 'f' || 'A' <= c && c <= 'F';
}

static signed char strtox_parse_digit(char c, char base) {
  if (!isalnum(c))
    return -1;
  if (isdigit(c)) {
    signed char val = c - '0';
    return val < base ? val : -1;
  }
  signed char val = tolower(c) - 'a' + 10;
  return val < base ? val : -1;
}

static const char *strtox_prelim(const char *p, char *sign, char *base) {
  /* skipping leading whitespace */
  while (isspace(*p))
    ++p;

  /* determining / skipping sign */
  if (*p != '+' && *p != '-')
    *sign = '+';
  else
    *sign = *(p++);

  /* determining base */
  if (*p == '0') {
    ++p;

    if ((*base == 0 || *base == 16) && (*p == 'x' || *p == 'X')) {
      *base = 16;
      ++p;

      /* catching a border case here: "0x" followed by a non-digit should
         be parsed as the unprefixed zero.
         We have to "rewind" the parsing; having the base set to 16 if it
         was zero previously does not hurt, as the result is zero anyway.
      */
      if (!is_hex_digit(*p))
        p -= 2;
    } else if (*base == 0) {
      *base = 8;
      /* back up one digit, so that a plain zero is decoded correctly
         (and endptr is set correctly as well).
         (2019-01-15, Giovanni Mascellani)
      */
      --p;
    } else {
      --p;
    }
  } else if (!*base) {
    *base = 10;
  }

  return p;
}

typedef struct {
  char *bytes;
  char sz;
} vintptr;

#define MAKE_VINTPTR(x)                                                        \
  { (char *)&x, sizeof(x) }

static void vintptr_dump(vintptr v) {
  for (char i = 0; i < v.sz; ++i)
    printf("%02x", v.bytes[i]);
  putchar('\n');
}

static void vintptr_zero(vintptr v) {
  for (char i = 0; i < v.sz; ++i)
    v.bytes[i] = 0;
}

static void vintptr_set(vintptr dst, vintptr src) {
  for (char i = 0; i < dst.sz; ++i)
    dst.bytes[i] = src.bytes[i];
}

static bool vintptr_ult(vintptr l, vintptr r) {
  for (char i = l.sz - 1; i; --i) {
    if (l.bytes[i] < r.bytes[i])
      return true;
    if (l.bytes[i] > r.bytes[i])
      return false;
  }
  return l.bytes[0] < r.bytes[0];
}

static bool vintptr_ne(vintptr l, vintptr r) {
  for (char i = 0; i < l.sz; ++i)
    if (l.bytes[i] != r.bytes[i])
      return true;
  return false;
}

static bool vintptr_eq(vintptr l, vintptr r) { return !vintptr_ne(l, r); }

static void vintptr_add(vintptr l, vintptr r) {
  unsigned char carry = 0;
  for (char i = 0; i < l.sz; ++i)
    l.bytes[i] = __builtin_addcb(l.bytes[i], r.bytes[i], carry, &carry);
}

static void vintptr_addc(vintptr l, char r) {
  unsigned char carry = 0;
  l.bytes[0] = __builtin_addcb(l.bytes[0], r, carry, &carry);
  for (char i = 1; i < l.sz; ++i)
    l.bytes[i] = __builtin_addcb(l.bytes[i], 0, carry, &carry);
}

static void vintptr_shl(vintptr v) {
  char carry = 0;
  for (char i = 0; i < v.sz; ++i) {
    char new_carry = v.bytes[i] & 0x80 ? 1 : 0;
    v.bytes[i] <<= 1;
    v.bytes[i] |= carry;
    carry = new_carry;
  }
}

static void vintptr_mul(vintptr l, char r) {
  uintmax_t pspace;
  vintptr p = {(char *)&pspace, l.sz};
  vintptr_zero(p);
  while (true) {
    if (r & 1) {
      --r;
      vintptr_add(p, l);
    }
    if (!r)
      break;
    r >>= 1;
    vintptr_shl(l);
  }

  vintptr_set(l, p);
}

static bool strtox_main(const char **p, char base, vintptr error,
                        vintptr limval, char limdigit, vintptr rc) {
  vintptr_zero(rc);

  signed char digit = strtox_parse_digit(**p, base);
  if (digit < 0) {
    *p = NULL;
    return false;
  }

  do {
    if (vintptr_ult(rc, limval) ||
        (vintptr_eq(rc, limval) && (digit <= limdigit))) {
      vintptr_mul(rc, base);
      vintptr_addc(rc, digit);
      ++(*p);
    } else {
      errno = ERANGE;

      while (strtox_parse_digit(**p, base) != -1)
        ++(*p);

      vintptr_set(rc, error);
      return true;
    }
  } while ((digit = strtox_parse_digit(**p, base)) >= 0);

  return false;
}

__attribute__((weak)) long strtol(const char *__restrict__ nptr,
                                  char **__restrict endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  long rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  long error;
  long limval;
  char limdigit;
  if (sign == '+') {
    error = LONG_MAX;
    limval = LONG_MAX / cbase;
    limdigit = LONG_MAX % cbase;
  } else {
    error = LONG_MIN;
    limval = LONG_MIN / -cbase;
    limdigit = -(LONG_MIN % cbase);
  }
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) long long strtoll(const char *__restrict__ nptr,
                                        char **__restrict__ endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  long long rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  long long error;
  long long limval;
  char limdigit;
  if (sign == '+') {
    error = LLONG_MAX;
    limval = LLONG_MAX / cbase;
    limdigit = LLONG_MAX % cbase;
  } else {
    error = LLONG_MIN;
    limval = LLONG_MIN / -cbase;
    limdigit = -(LLONG_MIN % cbase);
  }
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) unsigned long
strtoul(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  unsigned long rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  unsigned long error = ULONG_MAX;
  unsigned long limval = ULONG_MAX / cbase;
  char limdigit = ULONG_MAX % cbase;
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) unsigned long long
strtoull(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  unsigned long long rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  unsigned long long error = ULLONG_MAX;
  unsigned long long limval = ULLONG_MAX / cbase;
  char limdigit = ULLONG_MAX % cbase;
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) signed char strtosc(const char *__restrict__ nptr,
                                          char **__restrict endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  signed char rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  signed char error;
  signed char limval;
  char limdigit;
  if (sign == '+') {
    error = SCHAR_MAX;
    limval = SCHAR_MAX / cbase;
    limdigit = SCHAR_MAX % cbase;
  } else {
    error = SCHAR_MIN;
    limval = SCHAR_MIN / -cbase;
    limdigit = -(SCHAR_MIN % cbase);
  }
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) unsigned char
strtouc(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  unsigned char rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  unsigned char error = UCHAR_MAX;
  unsigned char limval = UCHAR_MAX / cbase;
  char limdigit = UCHAR_MAX % cbase;
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) int strtoi(const char *__restrict__ nptr,
                                 char **__restrict endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  int rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  int error;
  int limval;
  char limdigit;
  if (sign == '+') {
    error = INT_MAX;
    limval = INT_MAX / cbase;
    limdigit = INT_MAX % cbase;
  } else {
    error = INT_MIN;
    limval = INT_MIN / -cbase;
    limdigit = -(INT_MIN % cbase);
  }
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}

__attribute__((weak)) unsigned int
strtoui(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  unsigned int rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  unsigned int error = UINT_MAX;
  unsigned int limval = UINT_MAX / cbase;
  char limdigit = UINT_MAX % cbase;
  vintptr verror = MAKE_VINTPTR(error);
  vintptr vlimval = MAKE_VINTPTR(limval);
  vintptr vrc = MAKE_VINTPTR(rc);
  bool is_error = strtox_main(&p, cbase, verror, vlimval, limdigit, vrc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  return (sign == '+' || is_error) ? rc : -rc;
}
