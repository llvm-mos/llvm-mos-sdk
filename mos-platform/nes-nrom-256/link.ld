/* NES-NROM-256 iNES file linker script. */

MEMORY {
  /* CPU address space. */
  prg_rom (rx) : ORIGIN = 0x8000, LENGTH = 0x8000
}

INCLUDE nes-nrom.ld
