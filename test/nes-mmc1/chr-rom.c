#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

__attribute__((used, section(".chr_rom_0")))  const char cr0[4096] =  {1, [4095] = 2};
__attribute__((used, section(".chr_rom_31"))) const char cr31[4096] = {3, [4095] = 4};

char read_ppu(unsigned ppu_addr) {
  (void)PPU.status;
  PPU.vram.address = (unsigned)ppu_addr >> 8;
  PPU.vram.address = (unsigned)ppu_addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

void set_4k_banks(void) {
  POKE(0x8000, 0);
  POKE(0x8000, 0);
  POKE(0x8000, 1);
  POKE(0x8000, 1);
  POKE(0x8000, 1);
}

void set_bank_0(char b) {
  POKE(0xa000, b);
  b >>= 1;
  POKE(0xa000, b);
  b >>= 1;
  POKE(0xa000, b);
  b >>= 1;
  POKE(0xa000, b);
  b >>= 1;
  POKE(0xa000, b);
}

void set_bank_1(char b) {
  POKE(0xc000, b);
  b >>= 1;
  POKE(0xc000, b);
  b >>= 1;
  POKE(0xc000, b);
  b >>= 1;
  POKE(0xc000, b);
  b >>= 1;
  POKE(0xc000, b);
}

int main(void) {
  set_4k_banks();

  set_bank_0(0);
  set_bank_1(31);
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(4095) != 2)
    return EXIT_FAILURE;
  if (read_ppu(4096) != 3)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 4)
    return EXIT_FAILURE;

  set_bank_1(0);
  if (read_ppu(4096) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
