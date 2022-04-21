/* NES SLROM iNES file linker script. */

INCLUDE nes.ld

MEMORY {
  /* PRG-ROM VMAs. */
  prg_rom_lo : ORIGIN = 0x8000, LENGTH = 0x4000
  prg_rom_hi : ORIGIN = 0xc000, LENGTH = 0x4000

  /* PRG-ROM LMA. 256 Kib. */
  prg_rom : ORIGIN = 0x10000, LENGTH = 0x40000

  /* PRG-ROM Bank 15 LMA; accessible at startup at VMA prg_rom_hi. */
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
  __data_load_start = LOADADDR(.data) - ORIGIN(prg_rom_15) + ORIGIN(prg_rom_hi);
  __data_size = SIZEOF(.data);
  INCLUDE bss.ld
  INCLUDE noinit.ld

  .vector 0xfffa - ORIGIN(prg_rom_hi) + ORIGIN(prg_rom_15) : {
    SHORT(nmi) SHORT(_start) SHORT(irq)
  } >prg_rom_15
}

INCLUDE ines.ld
