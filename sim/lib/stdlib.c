#include <stdlib.h>

void abort(void) {
  // Writing to this IO register causes the simulator to abort.
  (*(volatile char *)0xFFF7) = 1;
  __builtin_unreachable();
}

void exit(int status) {
  // Writing to this IO register causes the simulator to exit with the given status.
  (*(volatile char *)0xFFF8) = (char)status;
  __builtin_unreachable();
}
