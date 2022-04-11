/* NES-NROM iNES file linker script. */

MEMORY {
  /* CPU address space. */
  ram (w)      : ORIGIN = 0x0200, LENGTH = 0x0600

  /* CHR-ROM VMA. */
  ppu_chr_rom : ORIGIN = 0x0000, LENGTH = 0x2000

  /**
   * CHR-ROM LMA. Doesn't correspond to anything at runtime; this is beyond
   * 0xffff to make sure that all LMAs are unique.
   */
  chr_rom : ORIGIN = 0x10000, LENGTH = 0x2000
}

SECTIONS {
  INCLUDE text.ld
  INCLUDE rodata.ld
  /* The data segment is loaded from PRG-ROM, but used in RAM. */
  .data : {
      __data_start = .;
      *(.data .data.*)
      __data_end = .;
  } AT>prg_rom
  __data_load_start = LOADADDR(.data);
  __data_size = SIZEOF(.data);
  INCLUDE bss.ld
  INCLUDE noinit.ld

  .chr_rom : { *(.chr_rom) } >ppu_chr_rom AT>chr_rom

  .vector 0xfffa : { SHORT(nmi) SHORT(_start) SHORT(irq) } >prg_rom
}

INCLUDE nes-imag-regs.ld
