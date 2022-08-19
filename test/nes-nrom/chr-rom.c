#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

__attribute__((used, section(".chr_rom")))  const char cr[4096] =  {1, [4095] = 2};

char read_ppu(unsigned ppu_addr) {
  (void)PPU.status;
  PPU.vram.address = (unsigned)ppu_addr >> 8;
  PPU.vram.address = (unsigned)ppu_addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

int main(void) {
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(4095) != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
