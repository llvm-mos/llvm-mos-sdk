#include <mapper.h>
#include <nes.h>
#include <peekpoke.h>
#include <stdlib.h>

__attribute__((used, section(".chr_rom_0")))
const char cr0[4096] = {1, [4095] = 2};
__attribute__((used, section(".chr_rom_31")))
const char cr31[4096] = {3, [4095] = 4};

char read_ppu(unsigned ppu_addr) {
  (void)PPU.status;
  PPU.vram.address = (unsigned)ppu_addr >> 8;
  PPU.vram.address = (unsigned)ppu_addr;
  (void)PPU.vram.data;
  return PPU.vram.data;
}

void set_4k_banks(void) { set_mmc1_ctrl(0b11100); }

int main(void) {
  set_4k_banks();

  set_chr_bank_0_retry(0);
  set_chr_bank_1_retry(31);
  if (read_ppu(0) != 1)
    return EXIT_FAILURE;
  if (read_ppu(4095) != 2)
    return EXIT_FAILURE;
  if (read_ppu(4096) != 3)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 4)
    return EXIT_FAILURE;

  set_chr_bank_1_retry(0);
  if (read_ppu(4096) != 1)
    return EXIT_FAILURE;
  if (read_ppu(8191) != 2)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
