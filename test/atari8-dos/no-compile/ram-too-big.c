// ExpectFailure: ld.lld: error: section '.data' will not fit in region 'ram'

#include <stdint.h>

// atari8-dos; presently we have 40KiB of RAM from 0x2000 to 0xC000,
// array sizes have to be <=32767; use 30+10
__attribute__((used)) uint8_t ram_too_big0[30 * 1024] = { 0x55 };
__attribute__((used)) uint8_t ram_too_big1[10 * 1024] = { 0xAA };

int main(void) {
  asm volatile(
    ""
    :
    : "r"(ram_too_big0)
    :
    );
  asm volatile(
    ""
    :
    : "r"(ram_too_big1)
    :
    );
}
