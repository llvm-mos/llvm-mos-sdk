#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

asm(".globl __chr_rom_size\n"
    "__chr_rom_size = 0\n"
    ".globl __chr_ram_size\n"
    "__chr_ram_size = 1024\n");

void set_bank(char b) {
  static const char rom_bytes[] = {0, [1]=1, [127]=127};
  POKE(&rom_bytes[b], b);
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
  set_bank(0);

  poke_ppu(0, 42);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;
  poke_ppu(8191, 43);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;
  if (peek_ppu(8191) != 43)
    return EXIT_FAILURE;

  set_bank(1);
  poke_ppu(0, 44);
  if (peek_ppu(0) != 44)
    return EXIT_FAILURE;

  set_bank(0);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;

  set_bank(127);
  poke_ppu(0, 45);
  if (peek_ppu(0) != 45)
    return EXIT_FAILURE;

  set_bank(1);
  if (peek_ppu(0) != 44)
    return EXIT_FAILURE;

  set_bank(0);
  if (peek_ppu(0) != 42)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
