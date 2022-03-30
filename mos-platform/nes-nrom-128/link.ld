/* NES-NROM-128 iNES file linker script. */

MEMORY {
  /* CPU address space. */
  ram (w)      : ORIGIN = 0x0200, LENGTH = 0x0600

  /**
   * Note: This is mirrored at 0x8000 and 0xC000, but the 6502 vectors are at
   * 0xFFFA, so using the 0xC000 mirror makes their placement clearer.
   */
  prg_rom (rx) : ORIGIN = 0xC000, LENGTH = 0x4000

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

/* Provide imaginary (zero page) registers. */
PROVIDE(__rc0 = 0x0000);
INCLUDE imag_regs.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

OUTPUT_FORMAT {
  /* Identification string: NES<EOF> */
  BYTE(0x4e) BYTE(0x45) BYTE(0x53) BYTE(0x1a)

  /* PRG-ROM size LSB (counting by 16K) */
  BYTE(1)
  /* CHR-ROM size LSB (counting by 8K) */
  BYTE(1)

  /* Flags 6:
    *   Mapper 0
    *   No hard-wired four-screen mode.
    *   No trainer.
    *   No battery.
    *   Horizontal hard-wired nametable mirroring type.
    */
  BYTE(0)

  /* Flags 7:
    *   Mapper 0.
    *   NES 2.0 identifier.
    *   NES/Family Computer console type.
    */
  BYTE(8)

  /* Mapper MSB/Submapper:
    *   Submapper 0.
    *   Mapper 0.
    */
  BYTE(0)

  /* PRG-ROM/CHR-ROM size MSB (counting by 8K) :
    *   16K PRG-ROM.
    *   8K  CHR-ROM.
    */
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

  /* CPU/PPU Timing
    *   NTSC NES
    */
  BYTE(0)

  /* VS system type/Extended Console Type: N/A */
  BYTE(0)

  /* Miscellaneous ROMs: 0 */
  BYTE(0)

  /* Default Expansion Device: N/A */
  BYTE(0)

  /* After the header, dump the full contents of the ROMs. */
  FULL(prg_rom)
  FULL(chr_rom)
}
