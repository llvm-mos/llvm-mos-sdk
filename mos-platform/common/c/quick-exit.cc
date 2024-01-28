#include "atexit-impl.h"

#include <stdlib.h>

using namespace __impl;

static RegistrationList quick_exit_list;

extern "C" {

// Implemented under the assumption that there is only a single loaded binary,
// with no dynamic loading. Accordingly, the mechanism for holding a DSO handle
// (the third parameter) is ignored.
int __cxa_at_quick_exit(void (*f)(void *), void *p, void * /* dso_handle */) {
  // Return values equal to C/C++ atexit() return value.
  return !quick_exit_list.push_front(ExitFunctionStorage{f, p});
}

int at_quick_exit(void (*function)(void)) {
  return __cxa_at_quick_exit(reinterpret_cast<void (*)(void *)>(function),
                             nullptr, nullptr);
}

_Noreturn void quick_exit(int status) {
  quick_exit_list.run_all_exits();
  _Exit(status);
}

} // extern "C"
