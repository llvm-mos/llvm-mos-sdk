// Copyright 2024 LLVM-MOS
//
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <string.h>

// Copying functions

__attribute__((weak)) char *strcpy(char *restrict s1, const char *restrict s2) {
  char *ret = s1;
  for (;; ++s1, ++s2) {
    *s1 = *s2;
    if (!*s1)
      return ret;
  }
}

__attribute__((weak)) char *strncpy(char *restrict s1, const char *restrict s2,
                                    size_t n) {
  char *ret = s1;
  for (; n; ++s1, ++s2, --n) {
    *s1 = *s2;
    if (!*s2) {
      for (++s1, --n; n; ++s1, --n)
        *s1 = '\0';
      break;
    }
  }
  return ret;
}

// Concatenation functions

__attribute__((weak)) char *strcat(char *restrict s1, const char *restrict s2) {
  size_t len = strlen(s1);
  strcpy(s1 + len, s2);
  return s1;
}

__attribute__((weak)) char *strncat(char *restrict s1, const char *restrict s2,
                                    size_t n) {
  size_t len = strlen(s1);
  if (strlen(s2) < n) {
    strcpy(s1 + len, s2);
  } else {
    strncpy(s1 + len, s2, n);
  }
  return s1;
}

// Comparison functions

__attribute__((weak)) int strcmp(const char *s1, const char *s2) {
  for (;; ++s1, ++s2) {
    if (!*s1 || !*s2 || *s1 != *s2)
      return *s1 - *s2;
  }
}

__attribute__((weak)) int strncmp(const char *s1, const char *s2, size_t n) {
  for (;; ++s1, ++s2, --n) {
    if (!n)
      return 0;
    if (!*s1 || !*s2 || *s1 != *s2)
      return *s1 - *s2;
  }
}

// Search functions

__attribute__((weak)) char *strchr(const char *s, int c) {
  char ch = (char)c;
  for (;; ++s) {
    if (*s == ch)
      return (char *)s;
    if (!*s)
      return NULL;
  }
}

// Originally from the Public Domain C Library (PDCLib).
__attribute__((weak)) size_t strcspn(const char *s1, const char *s2) {
  size_t len = 0;
  while (s1[len]) {
    const char *p = s2;

    while (*p)
      if (s1[len] == *p++)
        return len;

    ++len;
  }

  return len;
}

__attribute__((weak)) char *strpbrk(const char *s1, const char *s2) {
  s1 += strcspn(s1, s2);
  return *s1 ? (char *)s1 : NULL;
}

__attribute__((weak)) char *strrchr(const char *s, int c) {
  char ch = (char)c;
  const char *last = NULL;
  for (; *s; ++s)
    if (*s == ch)
      last = s;
  return (char *)last;
}

__attribute__((weak)) size_t strspn(const char *s1, const char *s2) {
  const char *a, *b;

  for (a = s1; *a; a++) {
    for (b = s2; *b && *b != *a; b++)
      ;
    if (!*b)
      break;
  }
  return a - s1;
}

// Originally from the Public Domain C Library (PDCLib).
char *strstr(const char *s1, const char *s2) {
  while (*s1) {
    const char *p1 = s1;
    const char *p2 = s2;

    while (*p2 && (*p1 == *p2)) {
      ++p1;
      ++p2;
    }

    if (!*p2)
      return (char *)s1;
    ++s1;
  }

  return NULL;
}

// Miscellaneous functions

__attribute__((weak)) size_t strlen(const char *s) {
  size_t len = 0;
  for (; *s; ++s)
    ++len;
  return len;
}

__attribute__((weak)) char *_strrev(char *str) {
  size_t len = strlen((const char *)str);
  for (size_t i = 0, j = len - 1; i < j; i++, j--) {
    char a = str[i];
    str[i] = str[j];
    str[j] = a;
  }
  return str;
}

__attribute__((weak)) char *strtok(char *__restrict__ s1,
                                   const char *__restrict__ s2) {
  static char *savestring = NULL;

  if (s1 == NULL) {
    s1 = savestring;
    if (s1 == NULL)
      return (char *)NULL;
  }

  char *a = s1 + strspn(s1, s2);
  if (!*a) {
    savestring = NULL;
    return (char *)NULL;
  }

  char *b = strpbrk(a, s2);
  if (b != NULL)
    *b++ = '\0';
  savestring = b;
  return a;
}
