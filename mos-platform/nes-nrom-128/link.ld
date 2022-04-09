/* NES-NROM-128 iNES file linker script. */

MEMORY {
  /**
   * Note: This is mirrored at 0x8000 and 0xC000, but the 6502 vectors are at
   * 0xFFFA, so using the 0xC000 mirror makes their placement clearer.
   */
  prg_rom (rx) : ORIGIN = 0xC000, LENGTH = 0x4000
}

INCLUDE nes-nrom.ld

OUTPUT_FORMAT {
  INCLUDE ines-header.ld

  /* PRG-ROM size LSB (counting by 16K) */
  BYTE(1)
  /* CHR-ROM size LSB (counting by 8K) */
  BYTE(1)

  INCLUDE ines-flags.ld

  FULL(prg_rom)
  FULL(chr_rom)
}
