// Copyright 2024 LLVM-MOS
//
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdlib.h>

// Originally from the Public Domain C Library (PDCLib).

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *)) {
  const void *pivot;
  int rc;
  size_t corr;

  while (nmemb) {
    /* algorithm needs -1 correction if remaining elements are an even number.
     */
    corr = nmemb % 2;
    nmemb /= 2;
    pivot = (const char *)base + (nmemb * size);
    rc = compar(key, pivot);

    if (rc > 0) {
      base = (const char *)pivot + size;
      /* applying correction */
      nmemb -= (1 - corr);
    } else if (rc == 0) {
      return (void *)pivot;
    }
  }

  return NULL;
}
