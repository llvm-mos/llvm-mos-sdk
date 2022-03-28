#include "ppu.h"

void __ppu_wait_vblank() {
  while (!(PPUSTATUS & 0x80))
    ;
}
void ppu_wait_vblank() __attribute((weak, alias("__ppu_wait_vblank")));

void __ppu_write_addr(unsigned short addr) {
  (void)PPUSTATUS;
  PPUADDR = addr >> 8;
  PPUADDR = addr & 0xff;
}
void ppu_write_addr(unsigned short addr)
    __attribute((weak, alias("__ppu_write_addr")));
