#include <mapper.h>
#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

MAPPER_CHR_ROM_KB(32);
MAPPER_CHR_RAM_KB(0);

__attribute__((used, section(".chr_rom_0")))
const char cr0[8192] = {1, [8191] = 2};
__attribute__((used, section(".chr_rom_3")))
const char cr3[8192] = {3, [8191] = 4};

volatile char frame_count;

asm(".section .nmi,\"ax\",@progbits\n"
    "inc frame_count\n");

void ppu_wait_vblank(void) {
  char next_frame_count = frame_count + 1;
  while (frame_count != next_frame_count)
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
  split_chr_bank(3);
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
  swap_chr_bank(3);
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
