// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdlib.h>

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <limits>
#include <signal.h>
#include <stdint.h>

#include "varint.h"

using namespace __impl;

// Originally from the Public Domain C Library (PDCLib).

// atox implementation

namespace {

void atox(const char *s, VarInt &rc) {
  rc.zero();
  char sign = '+';
  const char *x;

  while (isspace(*s))
    ++s;

  if (*s == '+')
    ++s;
  else if (*s == '-')
    sign = *(s++);

  while (isdigit(*s)) {
    rc *= 10;
    rc += *s - '0';
    ++s;
  }
  if (sign != '+')
    rc.negate();
}

} // namespace

extern "C" {

__attribute__((weak)) int atoi(const char *nptr) {
  BigInt<sizeof(int)> rc;
  atox(nptr, rc);
  return rc;
}

__attribute__((weak)) long atol(const char *nptr) {
  BigInt<sizeof(long)> rc;
  atox(nptr, rc);
  return rc;
}

__attribute__((weak)) long long atoll(const char *nptr) {
  BigInt<sizeof(long long)> rc;
  atox(nptr, rc);
  return rc;
}

} // extern "C"

// strtox implementation

namespace {

bool is_hex_digit(char c) {
  return isdigit(c) || 'a' <= c && c <= 'f' || 'A' <= c && c <= 'F';
}

signed char strtox_parse_digit(char c, char base) {
  if (!isalnum(c))
    return -1;
  if (isdigit(c)) {
    signed char val = c - '0';
    return val < base ? val : -1;
  }
  signed char val = tolower(c) - 'a' + 10;
  return val < base ? val : -1;
}

const char *strtox_prelim(const char *p, char *sign, char *base) {
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

bool strtox_main(const char **p, char base, const VarInt &error,
                 const VarInt &limval, char limdigit, VarInt &rc) {
  rc.zero();

  signed char digit = strtox_parse_digit(**p, base);
  if (digit < 0) {
    *p = NULL;
    return false;
  }

  do {
    if (rc < limval || (rc == limval && digit <= limdigit)) {
      rc *= base;
      rc += digit;
      ++(*p);
    } else {
      errno = ERANGE;

      while (strtox_parse_digit(**p, base) != -1)
        ++(*p);

      rc = error;
      return true;
    }
  } while ((digit = strtox_parse_digit(**p, base)) >= 0);

  return false;
}

template <typename T,
          typename std::enable_if_t<std::is_signed_v<T>, bool> = true>
T strto(const char *__restrict__ nptr, char **__restrict endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  BigInt<sizeof(T)> rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  BigInt<sizeof(T)> error;
  BigInt<sizeof(T)> limval;
  char limdigit;
  if (sign == '+') {
    error = std::numeric_limits<T>::max();
    limval = static_cast<T>(std::numeric_limits<T>::max() / cbase);
    limdigit = std::numeric_limits<T>::max() % cbase;
  } else {
    error = std::numeric_limits<T>::min();
    limval = static_cast<T>(std::numeric_limits<T>::min() / -cbase);
    limdigit = -(std::numeric_limits<T>::min() % cbase);
  }

  bool is_error = strtox_main(&p, cbase, error, limval, limdigit, rc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  if (sign != '+' && !is_error)
    rc.negate();
  return rc;
}

template <typename T,
          typename std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
T strto(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  if (base && (base < 2 || base > 36))
    return 0;

  BigInt<sizeof(T)> rc;
  char sign = '+';
  char cbase = base;
  const char *p = strtox_prelim(nptr, &sign, &cbase);
  if (!cbase)
    return 0;

  BigInt<sizeof(T)> error = std::numeric_limits<T>::max();
  BigInt<sizeof(T)> limval =
      static_cast<T>(std::numeric_limits<T>::max() / cbase);
  char limdigit = static_cast<T>(std::numeric_limits<T>::max() % cbase);
  bool is_error = strtox_main(&p, cbase, error, limval, limdigit, rc);

  if (endptr != NULL)
    *endptr = (p != NULL) ? (char *)p : (char *)nptr;

  if (sign != '+' && !is_error)
    rc.negate();
  return rc;
}

} // namespace

extern "C" {

__attribute__((weak)) long strtol(const char *__restrict__ nptr,
                                  char **__restrict endptr, int base) {
  return strto<long>(nptr, endptr, base);
}

__attribute__((weak)) long long strtoll(const char *__restrict__ nptr,
                                        char **__restrict__ endptr, int base) {
  return strto<long long>(nptr, endptr, base);
}

__attribute__((weak)) unsigned long
strtoul(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  return strto<unsigned long>(nptr, endptr, base);
}

__attribute__((weak)) unsigned long long
strtoull(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  return strto<unsigned long long>(nptr, endptr, base);
}

__attribute__((weak)) signed char _strtosc(const char *__restrict__ nptr,
                                           char **__restrict endptr, int base) {
  return strto<signed char>(nptr, endptr, base);
}

__attribute__((weak)) unsigned char
_strtouc(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  return strto<unsigned char>(nptr, endptr, base);
}

__attribute__((weak)) int _strtoi(const char *__restrict__ nptr,
                                  char **__restrict endptr, int base) {
  return strto<int>(nptr, endptr, base);
}

__attribute__((weak)) unsigned int
_strtoui(const char *__restrict__ nptr, char **__restrict__ endptr, int base) {
  return strto<unsigned int>(nptr, endptr, base);
}

} // extern "C"

// A 16-bit xorshift generator with constants well suited to 8-bit systems.
// Values found by George Marsaglia for the Z80:
//   http://www.retroprogramming.com/2017/07/xorshift-pseudorandom-numbers-in-z80.html

static unsigned seed = 1;

extern "C" {

__attribute__((weak)) int rand(void) {
  unsigned x = seed;
  x ^= x << 7;
  x ^= x >> 9;
  x ^= x << 8;
  return seed = x;
}

__attribute__((weak)) void srand(unsigned s) { seed = s; }

// Communication with the environment

__attribute__((weak)) _Noreturn void abort(void) {
  raise(SIGABRT);
  // A SIGABRT handler may have returned, but abort must terminate the program
  // regardless.
  _Exit(128 + SIGABRT);
}

__attribute__((weak)) char *getenv(const char *name) {
  // In the absence of a target-specific meaning for "environment list", always
  // report that the given name could not be found.
  return NULL;
}

__attribute__((weak)) int system(const char *string) {
  // In the absence of a target-specific meaning for "command processor", report
  // that none is present.
  return 0;
}

} // extern "C"
