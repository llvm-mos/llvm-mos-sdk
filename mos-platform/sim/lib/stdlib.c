#include <stdlib.h>

void abort(void) {
  // Writing to this IO register causes the simulator to abort.
  (*(volatile char *)0xFFF7) = 1;

  // Prevent the compiler from considering this entire basic block unreachable.
  __attribute__((leaf)) asm volatile ("");

  __builtin_unreachable();
}

void _exit(int status) {
  // Writing to this IO register causes the simulator to exit with the given status.
  (*(volatile char *)0xFFF8) = (char)status;

  // Prevent the compiler from considering this entire basic block unreachable.
  __attribute__((leaf)) asm volatile ("");

  __builtin_unreachable();
}
__attribute__((alias("_exit"))) void _Exit(int status);

unsigned long clock() {
  // reading first byte latches whole 32-bit value
  // so it needs to be read byte by byte in correct order
  unsigned long ticks;
  for(int i=0; i < 4; i++) {
    ((char *)&ticks)[i] = *((volatile char *)0xFFF0 + i);
  }
  return ticks;
}

void reset_clock() {
  *((volatile char *)0xFFF0) = 0;
}
