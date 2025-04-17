#include "atexit-impl.h"

using namespace __impl;

static RegistrationList atexit_list;

extern "C" {

asm(".section .fini.100,\"ax\",@progbits\n"
    "jsr __do_atexit\n");

void __do_atexit() { atexit_list.run_all_exits(); }

// atexit / finalize are implemented under the assumption that there is only a
// single loaded binary, with no dynamic loading.  Therefore; the mechanism for
// holding a DSO handle (the third parameter to _cxa_atexit), is ignored.
int __cxa_atexit(void (*f)(void *), void *p, void * /* dso_handle */) {
  // Return values equal to C/C++ atexit() return value.
  return !atexit_list.push_front(ExitFunctionStorage{f, p});
}

int atexit(void (*function)(void)) {
  return __cxa_atexit(reinterpret_cast<void (*)(void *)>(function), nullptr,
                      nullptr);
}

} // extern "C"
