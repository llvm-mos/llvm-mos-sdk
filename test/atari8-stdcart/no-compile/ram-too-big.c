// ExpectFailure: ld.lld: error: section '.bss' will not fit in region 'ram': overflowed

#include <stdint.h>

// atari8-stdcart; we have 14.25 KiB of RAM from 0x700 to 0x4000
__attribute__((used)) uint8_t ram_too_big[15 * 1024];

int main(void) {
  asm volatile(
    ""
    :
    : "r"(ram_too_big)
    :
    );
}
