#include <mapper.h>
#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_CHR_ROM_KB(0);
MAPPER_CHR_RAM_KB(8);

void set_8k_banks(void) { set_mmc1_ctrl(0b01100); }

void poke_ppu(unsigned addr, char val) {
  PPU.vram.address = addr >> 8;
  PPU.vram.address = (char)addr;
  PPU.vram.data = val;
}

char peek_ppu(unsigned addr) {
  PPU.vram.address = addr >> 8;
  PPU.vram.address = (char)addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

int main(void) {
  set_8k_banks();
  poke_ppu(0x1234, 42);
  if (peek_ppu(0x1234) != 42)
    return EXIT_FAILURE;
  poke_ppu(0x5678, 43);
  if (peek_ppu(0x5678) != 43)
    return EXIT_FAILURE;
  if (peek_ppu(0x1234) != 42)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
