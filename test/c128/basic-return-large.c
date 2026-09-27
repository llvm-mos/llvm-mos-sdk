#include <stdint.h>
#include <stdlib.h>

/* Same as basic-return.c, but large enough that exit() and the data
 * save-basic's _Exit uses lie above $4000. Restoring BASIC's memory
 * configuration before exit() had finished made this run BASIC ROM as code.
 *
 * If the layout ever changes so that exit is below $4000 the test would prove
 * nothing, so it hangs instead (the runner reports no prompt). */

__attribute__((noinline, section(".text.pad"))) static void pad(void) {
  __asm__ volatile(".fill 17000, 1, 0xEA");
}

int main(void) {
  pad();
  if ((uintptr_t)&exit < 0x4000)
    for (;;)
      ;
  return 0;
}
