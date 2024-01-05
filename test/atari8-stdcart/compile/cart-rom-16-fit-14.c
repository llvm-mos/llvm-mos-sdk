
#include <stdint.h>

asm(".globl __cart_rom_size \n __cart_rom_size = 16");

// atari8-stdcard, 16 KiB
__attribute__((used)) uint8_t data_too_big[14 * 1024] = { 0x55 };

int main(void) {
  asm volatile(
    ""
    :
    : "r"(data_too_big)
    :
    );
}
