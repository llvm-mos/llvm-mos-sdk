#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

volatile char return_value;

__attribute__((noinline, section(".prg_rom_0.text"))) void bank_0_fn(void) {
  asm volatile("");
  return_value = 7;
}

__attribute__((noinline, section(".prg_rom_30.text"))) void bank_30_fn(void) {
  asm volatile("");
  return_value = 8;
}

int main(void) {
  banked_call(0, bank_0_fn);
  if (return_value != 7)
    return EXIT_FAILURE;

  banked_call(30, bank_30_fn);
  if (return_value != 8)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
