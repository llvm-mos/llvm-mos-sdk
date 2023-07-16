#include <bank.h>
#include <peekpoke.h>
#include <stdlib.h>

volatile const char c[15000] = {1, [14999] = 2};

__attribute__((section(".prg_rom_0.rodata"))) volatile const char d[15000] = {
    3, [14999] = 4};

__attribute__((section(".prg_rom_6.rodata"))) volatile const char e[15000] = {
    5, [14999] = 6};

__attribute__((noinline, section(".prg_rom_0.text"))) char bank_0_fn(void) {
  asm volatile("");
  return 7;
}

__attribute__((noinline, section(".prg_rom_6.text"))) char bank_6_fn(void) {
  asm volatile("");
  return 8;
}

int main(void) {
  if ((unsigned)c < 0xc000)
    return EXIT_FAILURE;
  if ((unsigned)d >= 0xc000)
    return EXIT_FAILURE;
  if ((unsigned)e >= 0xc000)
    return EXIT_FAILURE;
  if (c[0] != 1 || c[14999] != 2)
    return EXIT_FAILURE;

  set_prg_bank(0);
  if (c[0] != 1 || c[14999] != 2)
    return EXIT_FAILURE;
  if (d[0] != 3 || d[14999] != 4)
    return EXIT_FAILURE;

  set_prg_bank(6);
  if (c[0] != 1 || c[14999] != 2)
    return EXIT_FAILURE;
  if (e[0] != 5 || e[14999] != 6)
    return EXIT_FAILURE;

  set_prg_bank(0);
  if ((unsigned)bank_0_fn >= 0xc000 || bank_0_fn() != 7)
    return EXIT_FAILURE;

  set_prg_bank(6);
  if ((unsigned)bank_6_fn >= 0xc000 || bank_6_fn() != 8)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
