#include <stdlib.h>
#include <peekpoke.h>

asm(".globl __prg_rom_size\n__prg_rom_size=32\n");

volatile const char c[32000] = {1, [31999] = 2};

int main(void) {
  if (c[0] != 1)
    return EXIT_FAILURE;
  if (c[31999] != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
