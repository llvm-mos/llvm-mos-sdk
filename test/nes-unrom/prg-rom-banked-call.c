#include <bank.h>
#include <peekpoke.h>
#include <stdlib.h>

volatile char return_value;

__attribute__((noinline, section(".prg_rom_0.text"))) void bank_0_fn(void) {
  asm volatile("");
  return_value = 7;
}

__attribute__((noinline, section(".prg_rom_14.text"))) void bank_14_fn(void) {
  asm volatile("");
  return_value = 8;
}

int main(void) {
  banked_call(0, bank_0_fn);
  if (return_value != 7)
    return EXIT_FAILURE;

  banked_call(14, bank_14_fn);
  if (return_value != 8)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
