// atari8-stdcart 16 KiB ROM should be able to accommodate 14 KiB of
// RODATA

#include <stdint.h>

asm(".globl __cart_rom_size \n __cart_rom_size = 16");

const uint8_t data_should_fit[14 * 1024] = { 0x55 };

int main(void) {
  asm volatile(
    ""
    :
    : "r"(data_should_fit)
    :
    );
}
