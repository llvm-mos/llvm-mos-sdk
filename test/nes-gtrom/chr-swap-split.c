#include <nes.h>
#include <mapper.h>
#include <peekpoke.h>
#include <stdlib.h>

volatile char frame_count;

asm(".section .nmi,\"ax\",@progbits\n"
    "inc frame_count\n");

void ppu_wait_vblank(void) {
  char next_frame_count = frame_count + 1;
  while (frame_count != next_frame_count)
    ;
}

void write_ppu(unsigned addr, char val) {
  PPU.vram.address = addr >> 8;
  PPU.vram.address = (char)addr;
  PPU.vram.data = val;
}

char read_ppu(unsigned ppu_addr) {
  (void)PPU.status;
  PPU.vram.address = (unsigned)ppu_addr >> 8;
  PPU.vram.address = (unsigned)ppu_addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

int main(void) {
  set_chr_bank(0);
  write_ppu(0, 1);
  write_ppu(8191, 2);
  set_chr_bank(3);
  write_ppu(0, 3);
  write_ppu(8191, 4);

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
