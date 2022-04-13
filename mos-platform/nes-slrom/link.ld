/* NES SLROM iNES file linker script. */

MEMORY {
  /* CPU address space. */
  ram (w)      : ORIGIN = 0x0200, LENGTH = 0x0600

  /* PRG-ROM VMAs. */
  prg_rom_lo : ORIGIN = 0x8000, LENGTH = 0x4000
  prg_rom_hi : ORIGIN = 0xc000, LENGTH = 0x4000

  /* CHR-ROM VMAs. */
  chr_rom_lo : ORIGIN = 0x0000, LENGTH = 0x1000
  chr_rom_hi : ORIGIN = 0x1000, LENGTH = 0x1000

  /* PRG-ROM LMA. 256 Kib. */
  prg_rom : ORIGIN = 0x10000, LENGTH = 0x40000

  /* PRG-ROM Bank 15 LMA; accessible at startup. */
  prg_rom_15 (rx) : ORIGIN = 0x4c000, LENGTH = 0x4000

  /* CHR-ROM LMA. 128 Kib. */
  chr_rom : ORIGIN = 0x50000, LENGTH = 0x20000
}

SECTIONS {
  /* Code must be loadable at startup, which means PRG-ROM page 15. Code may be
   * placed in other pages, but this must be done manually. */
  .text : { INCLUDE text-sections.ld } >prg_rom_hi AT>prg_rom_15
  .rodata : { INCLUDE rodata-sections.ld } >prg_rom_hi AT>prg_rom_15
  /* The data segment is loaded from PRG-ROM page 15, but used in RAM. */
  .data : { INCLUDE data-sections.ld } AT>prg_rom_15
  INCLUDE data-symbols.ld
  INCLUDE bss.ld
  INCLUDE noinit.ld

  .vector 0xfffa - ORIGIN(prg_rom_hi) + ORIGIN(prg_rom_15) : {
    SHORT(nmi) SHORT(_start) SHORT(irq)
  } >prg_rom_15
}

INCLUDE nes-imag-regs.ld

OUTPUT_FORMAT {
  INCLUDE ines-header.ld

  /* PRG-ROM size LSB. */
  BYTE(16)

  /* CHR-ROM size LSB. */
  BYTE(16)

  /* Flags 6:
  *   Mapper 0
  *   No hard-wired four-screen mode.
  *   No trainer.
  *   No battery.
  *   No hard-wired mirroring.
  */
  BYTE(0)

  /* Flags 7:
  *   Mapper 1.
  *   NES 2.0 identifier.
  *   NES/Family Computer console type.
  */
  BYTE(1 << 4 | 2 << 2 | 0)

  /* Mapper MSB/Submapper:
  *   Submapper 0.
  *   Mapper MSB 0.
  */
  BYTE(0)

  /* PRG-ROM/CHR-ROM size MSB (counting by 8K) */
  BYTE(0)

  /* PRG-RAM/EEPROM size
  *   No PRG-RAM.
  *   No PRG-EEPROM.
  */
  BYTE(0)

  /* CHR-RAM/NVRAM size
  *   No CHR-RAM.
  *   No CHR-NVRAM.
  */
  BYTE(0)

  /* CPU/PPU Timing */
  BYTE(__timing)

  /* VS system type/Extended Console Type: N/A */
  BYTE(0)

  /* Miscellaneous ROMs: 0 */
  BYTE(0)

  /* Default Expansion Device: N/A */
  BYTE(0)

  FULL(prg_rom)
  FULL(chr_rom)
}
