#include <peekpoke.h>
#include <stdlib.h>

asm(".global __prg_ram_size\n__prg_ram_size=32\n");

__attribute__((section(".prg_ram_0.noinit"))) volatile char c[8192];

__attribute__((section(".prg_ram_3.noinit"))) volatile char d[4097];
__attribute__((section("_3.noinit"))) volatile char e[4095];

void set_prg_ram_bank(char b) { set_chr_bank_0(b << 2); }

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
