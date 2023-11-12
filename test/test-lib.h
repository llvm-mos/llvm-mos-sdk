#ifndef _TEST_LIB_H
#define _TEST_LIB_H

#include <stdbool.h>

#define SIGNATURE_SIZE 8

// The emutest runner expects to find one of two
// signatures in main RAM.
extern const char signature_pass[SIGNATURE_SIZE];
extern const char signature_fail[SIGNATURE_SIZE];

// this array will contain the test signature
extern char test_result[SIGNATURE_SIZE];

// set the test signature in RAM
void test_set_result(bool passed);

#endif
