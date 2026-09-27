#ifndef TEST_CHECK_H
#define TEST_CHECK_H

#include <stdlib.h>

// CHECK(cond) for tests that return EXIT_SUCCESS or EXIT_FAILURE from main (or
// from a helper returning int): a false condition records its line in
// test_fail_line and returns EXIT_FAILURE. vice-runner.py prints the line when
// the test fails. One test program per translation unit.
volatile unsigned test_fail_line __attribute__((used));

#define CHECK(c)                                                               \
  do {                                                                         \
    if (!(c)) {                                                                \
      test_fail_line = __LINE__;                                               \
      return EXIT_FAILURE;                                                     \
    }                                                                          \
  } while (0)

#endif // TEST_CHECK_H
