#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_PRG_ROM_KB(32);

volatile const char c[15000] = {1, [14999] = 2};

__attribute__((section(".prg_rom_0"))) volatile const char d[16372] = {
    3, [16371] = 4};

int main(void) {
  if (c[0] != 1)
    return EXIT_FAILURE;
  if (c[14999] != 2)
    return EXIT_FAILURE;
  set_prg_bank(0);
  if (d[0] != 3)
    return EXIT_FAILURE;
  if (d[16371] != 4)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
