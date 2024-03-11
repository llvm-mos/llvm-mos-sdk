#include <peekpoke.h>
#include <string.h>

#include "test-lib-emutest.h"

// The emutest runner expects to find one of two
// signatures in main RAM.
// These are encoded to avoid false positives: encoded_char = plain_char + 1
// the section attribute is because clang still wants to put it into the data section (TODO?)
__attribute__((section(".rodata"))) static const char signature_pass[SIGNATURE_SIZE] = "UftuQbtt"; // "TestPass";
__attribute__((section(".rodata"))) static const char signature_fail[SIGNATURE_SIZE] = "UftuGbjm"; // "TestFail";

#ifdef __NES__
// NES tests currently can't spare a byte
// so we'll just write wherever
#define test_result ((char*)0x180)
#else
// this array will contain the test signature
// (use macro because clang requires extension for constant array size?)
char test_result[SIGNATURE_SIZE];
#endif

// set pass/fail manually, if you can't use exit() 
void test_set_result(bool passed) {
  const char* const sig = passed ? signature_pass : signature_fail;
  for (int i=0; i<SIGNATURE_SIZE; i++) {
    test_result[i] = sig[i] - 1;
  }
}

bool test_has_result(bool passed) {
  const char* const sig = passed ? signature_pass : signature_fail;
  for (int i=0; i<SIGNATURE_SIZE; i++) {
    if (test_result[i] != sig[i] - 1)
      return false;
  }
  return true;
}

_Noreturn void _Exit(int status) {
  // For emutest, we put a pass/fail signature into the main RAM area.
  test_set_result(status == 0);
  // emutest needs us to hang here, so it can read the signature.
  while (1) ;
}
