#include <nes.h>
#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_CHR_ROM_KB(32);
MAPPER_CHR_RAM_KB(0);

__attribute__((used, section(".chr_rom_0")))
const char cr0[8192] = {1, [8191] = 2};
__attribute__((used, section(".chr_rom_3")))
const char cr3[8192] = {3, [8191] = 4};

char read_ppu(unsigned ppu_addr) {
  (void)PPU.status;
  PPU.vram.address = (unsigned)ppu_addr >> 8;
  PPU.vram.address = (unsigned)ppu_addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

int main(void) {
  set_chr_bank(0);
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;

  set_chr_bank(3);
  if (read_ppu(0) != 3)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 4)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
