
#include <stdint.h>

extern int __cart_rom_size;

int main(void) {
  asm volatile(
    ""
    :
    : "r"(__cart_rom_size)
    :
    );
}
