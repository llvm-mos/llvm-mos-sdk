/* NES-NROM-256 iNES file linker script. */

MEMORY {
  /* CPU address space. */
  prg_rom (rx) : ORIGIN = 0x8000, LENGTH = 0x8000
}

INCLUDE nes-nrom.ld

OUTPUT_FORMAT {
  INCLUDE ines-header.ld

  /* PRG-ROM size LSB (counting by 16K) */
  BYTE(2)
  /* CHR-ROM size LSB (counting by 8K) */
  BYTE(1)

  INCLUDE ines-flags.ld

  FULL(prg_rom)
  FULL(chr_rom)
}
