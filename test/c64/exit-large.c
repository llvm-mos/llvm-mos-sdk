#include <stdint.h>
#include <stdlib.h>

/* Regression test: a program large enough that exit() and its data end up at
 * $A000 or above, where BASIC's ROM is switched back in. The exit handlers used
 * to switch the ROM in before exit() had finished, so exit() returned into
 * ROM. Here the exit code and test-lib-emutest's _Exit (which reads its
 * signature from .rodata and writes test_result, both above $A000 too) must
 * still run, and report through the usual signature.
 *
 * The program checks its own premise: if the layout ever changes so that exit
 * or test_result are below $A000, the test would pass without exercising
 * anything, so it fails instead.
 */

extern char test_result[];

__attribute__((noinline, section(".text.pad"))) static void pad(void) {
  __asm__ volatile(".fill 40000, 1, 0xEA");
}

int main(void) {
  pad();
  if ((uintptr_t)&exit < 0xA000 || (uintptr_t)test_result < 0xA000)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
