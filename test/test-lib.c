#include <peekpoke.h>
#include <string.h>

#include "test-lib.h"

// The emutest runner expects to find one of two
// signatures in main RAM.
const char signature_pass[SIGNATURE_SIZE] = "TestPass";
const char signature_fail[SIGNATURE_SIZE] = "TestFail";

// this array will contain the test signature
// (use macro because clang requires extension for constant array size?)
__attribute__((section(".zp.bss"), used, retain)) char test_result[SIGNATURE_SIZE];

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
#ifdef __NES__
  // This is an unused APU test register, so it should be safe to use writing to
  // this address to report the exit code to the controlling Mesen Lua script.
  POKE(0x4018, status);
#endif
  // emutest needs us to hang here, so it can read the signature.
  while (1) ;
}
