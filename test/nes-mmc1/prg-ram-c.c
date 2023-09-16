#include <peekpoke.h>
#include <stdlib.h>

asm(".global __prg_ram_size\n__prg_ram_size=32\n");
asm(".global __chr_rom_size\n__chr_rom_size=16\n");

volatile char c[8100] = {1, [8099] = 2};

int main(void) {
  if (c[0] != 1 || c[8099] != 2)
    return EXIT_FAILURE;
  c[0] = 3;
  if (c[0] != 3)
    return EXIT_FAILURE;
  c[8099] = 4;
  if (c[8099] != 4)
    return EXIT_FAILURE;
  if (c[0] != 3)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
