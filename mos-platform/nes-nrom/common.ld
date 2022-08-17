/* Common elements of NES-NROM iNES file linker scripts. */

INCLUDE nes.ld

ASSERT(__prg_ram_size == 0 || __prg_nvram_size == 0,
       "Simulatenously using PRG-RAM and PRG-NVRAM is not supported.")
ASSERT(__chr_rom_size <= 8, "NROM only supports up to 8 KiB of CHR-ROM.")
ASSERT(__prg_rom_size == 16 || __prg_rom_size == 32,
       "NROM only supports 16 KiB or 32 KiB of PRG-ROM")
ASSERT(__prg_ram_size + __prg_nvram_size <= 8,
       "At most 8 KiB of PRG-(NV)RAM is supported.")

MEMORY {
  /* PRG-RAM VMA. */
  prg_ram : ORIGIN = 0x6000,
            LENGTH = MAX(0x2000, (__prg_ram_size + __prg_nvram_size) * 1024)

  /**
   * CHR-ROM LMA. Doesn't correspond to anything at runtime; this is beyond
   * 0xffff to make sure that all LMAs are unique.
   */
  chr_rom : ORIGIN = 0x10000, LENGTH = __chr_rom_size * 1024

  /**
   * Note: When __prg_rom_size == 16, PRG-ROM is mirrored at 0x8000 and 0xC000.
   * Since the 6502 vectors are at 0xFFFA, using the 0xC000 mirror makes their
   * placement more obvious.
   */
  prg_rom (rx) : ORIGIN = __prg_rom_size == 32 ? 0x8000 : 0xC000,
                 LENGTH = __prg_rom_size * 1024
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram
  .chr_rom : { KEEP(*(.chr_rom .chr_rom.*)) } >chr_rom

  INCLUDE text.ld
  INCLUDE rodata.ld
  .data : { INCLUDE data-sections.ld } >c_ram AT>prg_rom
  INCLUDE data-symbols.ld
  .bss (NOLOAD) : { INCLUDE bss-sections.ld } >c_ram
  INCLUDE bss-symbols.ld
  .noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >c_ram
  .vector 0xfffa : { SHORT(nmi) SHORT(_start) SHORT(irq) } >prg_rom
}

INCLUDE ines.ld
