#include "ppu.h"

#define __NES__
#include <nes.h>

void __ppu_wait_vblank() {
  while (!(PPU.status & 0x80))
    ;
}
void ppu_wait_vblank() __attribute((weak, alias("__ppu_wait_vblank")));

void __ppu_write_addr(unsigned short addr) {
  (void)PPU.status;
  PPU.vram.address = addr >> 8;
  PPU.vram.address = addr & 0xff;
}
void ppu_write_addr(unsigned short addr)
    __attribute((weak, alias("__ppu_write_addr")));
