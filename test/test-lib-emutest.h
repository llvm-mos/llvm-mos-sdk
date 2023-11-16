#ifndef _TEST_LIB_H
#define _TEST_LIB_H

#include <stdbool.h>

#define SIGNATURE_SIZE 8

// this array will contain the test signature
extern char test_result[SIGNATURE_SIZE];

// set the test signature in RAM
void test_set_result(bool passed);

// get the test result if previoulsy set
bool test_has_result(bool passed);

#endif
