#include <peekpoke.h>
#include <string.h>

#include "test-lib-emutest.h"

// The emutest runner expects to find one of two
// signatures in main RAM.
const char signature_pass[SIGNATURE_SIZE] = "TestPass";
const char signature_fail[SIGNATURE_SIZE] = "TestFail";

// this array will contain the test signature
// (use macro because clang requires extension for constant array size?)
char test_result[SIGNATURE_SIZE];

// set pass/fail manually, if you can't use exit() 
void test_set_result(bool passed) {
  if (passed) {
    memcpy(test_result, signature_pass, SIGNATURE_SIZE);
  } else {
    memcpy(test_result, signature_fail, SIGNATURE_SIZE);
  }
}

__attribute__((noreturn)) void _exit(int status) {
  // For emutest, we put a pass/fail signature into the main RAM area.
  test_set_result(status == 0);
  // emutest needs us to hang here, so it can read the signature.
  while (1) ;
}
