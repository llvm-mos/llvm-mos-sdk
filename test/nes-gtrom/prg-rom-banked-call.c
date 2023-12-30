#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

asm(".weak __prg_rom_size \n __prg_rom_size = 512 \n");

volatile char return_value;

__attribute__((noinline, section(".prg_rom_0.text"))) void bank_0_fn(void) {
  asm volatile("");
  return_value = 7;
}

__attribute__((noinline, section(".prg_rom_15.text"))) void bank_15_fn(void) {
  asm volatile("");
  return_value = 8;
}

int main(void) {
  banked_call(0, bank_0_fn);
  if (return_value != 7)
    return EXIT_FAILURE;

  banked_call(15, bank_15_fn);
  if (return_value != 8)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
