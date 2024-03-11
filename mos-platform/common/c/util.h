// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Utilities shared between disparate parts of the libc.

#ifndef _UTIL_H
#define _UTIL_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// State of a formatted input/output operation.
struct Status {
  signed char base; // base to which the value shall be converted
  uint16_t flags;   // flags and length modifiers
  size_t n;         // print: maximum characters to be written
                    // scan:  number matched conversion specifiers
  size_t i;         // number of characters read/written
  size_t current;   // number of characters read in current conversion
  char *s;          // *sprintf(): target buffer
                    // *sscanf():  source string
  size_t width;     // specified field width
  int prec;         // specified field precision
  va_list arg;      // argument stack
};

// Return the digit for a character in the given base or -1 if invalid.
signed char __parse_digit(char c, char base);

// A simple base-10 only strtoui. Overflows are undefined behavior. If there are
// no digits, it returns zero.
unsigned __simple_strtoui(const char *__restrict__ nptr,
                          char **__restrict endptr);

#ifdef __cplusplus
}
#endif

#endif // _UTIL_H
