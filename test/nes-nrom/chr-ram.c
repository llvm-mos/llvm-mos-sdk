#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

asm(".globl __chr_rom_size\n"
    "__chr_rom_size = 0\n"
    ".globl __chr_ram_size\n"
    "__chr_ram_size = 8\n");

void set_8k_banks(void) {
  POKE(0x8000, 0);
  POKE(0x8000, 0);
  POKE(0x8000, 1);
  POKE(0x8000, 1);
  POKE(0x8000, 0);
}

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
