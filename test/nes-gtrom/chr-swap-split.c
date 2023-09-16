#include <nes.h>
#include <bank.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_CHR_ROM_KB(16);
MAPPER_CHR_RAM_KB(0);

__attribute__((used, section(".chr_rom_0")))
const char cr0[8192] = {1, [8191] = 2};
__attribute__((used, section(".chr_rom_1")))
const char cr1[8192] = {3, [8191] = 4};

void ppu_wait_vblank(void) {
  while (!(PPU.status & 0x80))
    ;
}

char read_ppu(unsigned ppu_addr) {
  (void)PPU.status;
  PPU.vram.address = (unsigned)ppu_addr >> 8;
  PPU.vram.address = (unsigned)ppu_addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

int main(void) {
  // Enable NMI generation.
  PPU.control = 0x80;
  
  ppu_wait_vblank();

  // set changes immediately
  set_chr_bank(0);
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;
  ppu_wait_vblank();
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;

  // split changes until NMI (vblank)
  split_chr_bank(1);
  if (read_ppu(0) != 3)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 4)
    return EXIT_FAILURE;
  ppu_wait_vblank();
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;

  // swap changes after NMI (vblank)
  swap_chr_bank(1);
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;
  ppu_wait_vblank();
  if (read_ppu(0) != 3)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 4)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
