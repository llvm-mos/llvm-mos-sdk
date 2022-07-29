/* NES-NROM iNES file linker script. */

INCLUDE nes.ld

MEMORY {
  /**
   * CHR-ROM LMA. Doesn't correspond to anything at runtime; this is beyond
   * 0xffff to make sure that all LMAs are unique.
   */
  chr_rom : ORIGIN = 0x10000, LENGTH = 0x2000
}

SECTIONS {
  INCLUDE zp.ld
  INCLUDE text.ld
  INCLUDE rodata.ld
  /* The data segment is loaded from PRG-ROM, but used in RAM. */
  .data : { INCLUDE data-sections.ld } AT>prg_rom
  INCLUDE data-symbols.ld
  INCLUDE bss.ld
  INCLUDE noinit.ld
  INCLUDE chr-rom.ld

  .vector 0xfffa : { SHORT(nmi) SHORT(_start) SHORT(irq) } >prg_rom
}

INCLUDE ines.ld
