#include <stdlib.h>
#include <peekpoke.h>

asm(".global __prg_ram_size\n__prg_ram_size=8\n");

__attribute__((section(".prg_ram")))
volatile char c[8192];

int main(void) {
  c[0] = 1;
  if (c[0] != 1)
    return EXIT_FAILURE;
  c[8191] = 2;
  if (c[8191] != 2)
    return EXIT_FAILURE;
  if (c[0] != 1)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
