#include <stdlib.h>

void abort(void) {
  // Writing to this IO register causes the simulator to abort.
  (*(volatile char *)0xFFF7) = 1;
  __builtin_unreachable();
}