// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from the Public Domain C library (PDCLib).

#ifdef __cplusplus
extern "C" {
#endif

#include <__internal.h>

#ifndef _ASSERT_H
#define _ASSERT_H
void __assert(const char *file, const char *line, const char *function,
              const char *expr);
#endif

/* If NDEBUG is set, assert() is a null operation. */
#undef assert

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
// Breaking this apart by component saves space.
#define assert(expression)                                                     \
  ((expression) ? (void)0                                                      \
                : __assert(__FILE__, _VALUE_TO_STRING(__LINE__), __func__,     \
                           #expression))
#endif

#ifdef __cplusplus
}
#endif
