#include <nes.h>
#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_CHR_ROM_KB(0);
MAPPER_CHR_RAM_KB(32);

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
  set_chr_bank(0);

  poke_ppu(0, 42);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;
  poke_ppu(8191, 43);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;
  if (peek_ppu(8191) != 43)
    return EXIT_FAILURE;

  set_chr_bank(1);
  poke_ppu(0, 44);
  if (peek_ppu(0) != 44)
    return EXIT_FAILURE;

  set_chr_bank(0);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;

  set_chr_bank(3);
  poke_ppu(0, 45);
  if (peek_ppu(0) != 45)
    return EXIT_FAILURE;

  set_chr_bank(1);
  if (peek_ppu(0) != 44)
    return EXIT_FAILURE;

  set_chr_bank(0);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
