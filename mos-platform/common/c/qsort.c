// Copyright 2024 LLVM-MOS
//
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdlib.h>

// Originally from the Public Domain C Library (PDCLib).

/* This implementation is taken from Paul Edward's PDPCLIB.

   Original code is credited to Raymond Gardner, Englewood CO.
   Minor mods are credited to Paul Edwards.
   Some reformatting and simplification done by Martin Baute.
   All code is still Public Domain.
*/

static void memswp(char *i, char *j, size_t size) {
  char tmp;
  do {
    tmp = *i;
    *i++ = *j;
    *j++ = tmp;
  } while (--size);
}

/* For small sets, insertion sort is faster than quicksort.
   T is the threshold below which insertion sort will be used.
   Must be 3 or larger.
*/
#define THRESHOLD 7

/* Macros for handling the QSort stack */
#define PREPARE_STACK                                                          \
  char *stack[STACKSIZE];                                                      \
  char **stackptr = stack
#define PUSH(base, limit)                                                      \
  stackptr[0] = base;                                                          \
  stackptr[1] = limit;                                                         \
  stackptr += 2
#define POP(base, limit)                                                       \
  stackptr -= 2;                                                               \
  base = stackptr[0];                                                          \
  limit = stackptr[1]
/* TODO: Stack usage is log2( nmemb ) (minus what T shaves off the worst case).
         Worst-case nmemb is platform dependent and should probably be
         configured through _PDCLIB_config.h.
*/
#define STACKSIZE 16

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *)) {
  char *i;
  char *j;
  char *base_ = (char *)base;
  char *limit = base_ + nmemb * size;
  PREPARE_STACK;

  for (;;) {
    /* QSort for more than T elements. */
    if ((size_t)(limit - base_) > THRESHOLD * size) {
      /* We work from second to last - first will be pivot element. */
      i = base_ + size;
      j = limit - size;
      /* We swap first with middle element, then sort that with second
         and last element so that eventually first element is the median
         of the three - avoiding pathological pivots.
         TODO: Instead of middle element, chose one randomly.
      */
      memswp(((((size_t)(limit - base_)) / size) / 2) * size + base_, base_,
             size);

      if (compar(i, j) > 0)
        memswp(i, j, size);
      if (compar(base_, j) > 0)
        memswp(base_, j, size);
      if (compar(i, base_) > 0)
        memswp(i, base_, size);

      /* Now we have the median for pivot element, entering main Quicksort. */
      for (;;) {
        /* move i right until *i >= pivot */
        do
          i += size;
        while (compar(i, base_) < 0);

        /* move j left until *j <= pivot */
        do
          j -= size;
        while (compar(j, base_) > 0);

        /* break loop if pointers crossed */
        if (i > j)
          break;

        /* else swap elements, keep scanning */
        memswp(i, j, size);
      }

      /* move pivot into correct place */
      memswp(base_, j, size);

      /* larger subfile base / limit to stack, sort smaller */
      if (j - base_ > limit - i) {
        /* left is larger */
        PUSH(base_, j);
        base_ = i;
      } else {
        /* right is larger */
        PUSH(i, limit);
        limit = j;
      }
    } else {
      /* insertion sort for less than T elements */
      for (j = base_, i = j + size; i < limit; j = i, i += size) {
        for (; compar(j, j + size) > 0; j -= size) {
          memswp(j, j + size, size);

          if (j == base_)
            break;
        }
      }

      /* if any entries on stack  */
      if (stackptr != stack) {
        POP(base_, limit);
      } else {
        break;
      }
    }
  }
}
