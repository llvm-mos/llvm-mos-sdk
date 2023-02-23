#include <stdlib.h>
#include <peekpoke.h>

asm(".globl __prg_rom_size\n"
    "__prg_rom_size = 16\n");

volatile const char c[15000] = {1, [14999] = 2};

int main(void) {
  if (c[0] != 1)
    return EXIT_FAILURE;
  if (c[14999] != 2)
    return EXIT_FAILURE;
  if ((unsigned)c < 0xc000)
    return EXIT_FAILURE;
  if (PEEK((unsigned)c - 0xc000 + 0x8000) != 1)
    return EXIT_FAILURE;
  if (PEEK((unsigned)c - 0xc000 + 0x8000 + 14999) != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
