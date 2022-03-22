#include "divmod.h"

// These can are large enough to pull in the stack pointer, so break them out
// into a separate file so they can be compiled without LTO.
extern "C" {
unsigned long __udivmodsi4(unsigned long a, unsigned long b,
                           unsigned long *rem) {
  return udivmod(a, b, rem);
}
unsigned long long __udivmoddi4(unsigned long long a, unsigned long long b,
                                unsigned long long *rem) {
  return udivmod(a, b, rem);
}
long __divmodsi4(long a, long b, long *rem) { return divmod(a, b, rem); }
long long __divmoddi4(long long a, long long b, long long *rem) {
  return divmod(a, b, rem);
}
}
