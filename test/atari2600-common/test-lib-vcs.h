#ifndef TESTLIB_VCS_H
#define TESTLIB_VCS_H

// these functions set the test result and show
// a message on the screen

__attribute__((noreturn)) void test_passed();

__attribute__((noreturn)) void test_failed();

#endif
