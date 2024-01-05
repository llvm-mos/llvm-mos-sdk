// ExpectFailure: ld.lld: error: section '.data' will not fit in region 'cart_rom': overflowed

#include <stdint.h>

asm(".globl __cart_rom_size \n __cart_rom_size = 8");

// atari8-stdcard, 8 KiB, this won't fit
__attribute__((used)) uint8_t data_too_big[8 * 1024] = { 0x55 };

int main(void) {
  asm volatile(
    ""
    :
    : "r"(data_too_big)
    :
    );
}
