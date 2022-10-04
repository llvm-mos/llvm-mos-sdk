#include <nes.h>

static void ppu_wait_vblank(void) {
  while (!(PPU.status & 0x80))
    ;
}

static void ppu_write_addr(unsigned short addr) {
  (void)PPU.status;
  PPU.vram.address = addr >> 8;
  PPU.vram.address = addr & 0xff;
}

int main(void) {
  // Enable BG rendering.
  ppu_wait_vblank();
  PPU.mask = 0b00001000;

  char color = 0;
  for (;;) {
    // Wait for 0.5 second.
    for (int i = 0; i < 30; ++i)
      ppu_wait_vblank();

    // Increment the palette color 0.
    ppu_write_addr(0x3f00);
    PPU.vram.data = ++color;
  }
}
