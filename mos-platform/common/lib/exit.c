#include <stdlib.h>
#include <stdio.h>

extern void __exit(int status);

void exit(int status) {
  __exit(status);

  // Prevent the compiler from considering this entire basic block unreachable.
  asm volatile ("");

  __builtin_unreachable();
}