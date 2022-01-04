// place holder for stdlib "abort" function.
#include <stdio.h>

// Not sure what the best way to handle this is on C64.

void abort() {
  puts("ABORT() CALLED");

  for (;;) {}

  __builtin_unreachable();
}
