#include <stdlib.h>

#include "sim-io.h"

void __sigabrt(void) {
  // Writing to this IO register causes the simulator to abort.
  sim_reg_iface->abort = 1;

  // Prevent the compiler from considering this entire basic block unreachable.
  __attribute__((leaf)) asm volatile("");

  __builtin_unreachable();
}

void _Exit(int status) {
  // Writing to this IO register causes the simulator to exit with the given
  // status.
  sim_reg_iface->exit = (uint8_t)status;

  // Prevent the compiler from considering this entire basic block unreachable.
  __attribute__((leaf)) asm volatile("");

  __builtin_unreachable();
}

unsigned long clock() {
  // reading first byte latches whole 32-bit value
  // so it needs to be read byte by byte in correct order
  unsigned long ticks;
  for (int i = 0; i < 4; i++) {
    ((char *)&ticks)[i] = sim_reg_iface->clock[i];
  }
  return ticks;
}

void reset_clock() { sim_reg_iface->clock[0] = 0; }
