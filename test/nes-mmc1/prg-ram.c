#include <bank.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_PRG_RAM_KB(32);
MAPPER_CHR_ROM_KB(16);
MAPPER_PRG_ROM_KB(128);

__attribute__((section(".prg_ram_0.noinit"))) volatile char c[8192];

__attribute__((section(".prg_ram_3.noinit"))) volatile char d[4097];
__attribute__((section("_3.noinit"))) volatile char e[4095];

void set_prg_ram_bank(char b) {
  set_chr_bank_0_high(get_chr_bank_0_high() & 0b10000 | b << 2);
}

int main(void) {
  set_prg_ram_bank(0);
  c[0] = 1;
  if (c[0] != 1)
    return EXIT_FAILURE;
  c[8191] = 2;
  if (c[8191] != 2)
    return EXIT_FAILURE;
  if (c[0] != 1)
    return EXIT_FAILURE;

  set_prg_ram_bank(3);
  d[0] = 3;
  if (d[0] != 3)
    return EXIT_FAILURE;
  e[4094] = 4;
  if (e[4094] != 4)
    return EXIT_FAILURE;
  if (d[0] != 3)
    return EXIT_FAILURE;

  set_prg_ram_bank(0);
  if (c[0] != 1)
    return EXIT_FAILURE;
  if (c[8191] != 2)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
