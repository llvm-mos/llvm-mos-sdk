/* NES-NROM iNES file linker script. */

INCLUDE nes.ld

ASSERT(__chr_rom_size <= 1, "NROM only supports up to 8 KiB of CHR-ROM.")
ASSERT(__prg_rom_size == 1 || __prg_rom_size == 2,
       "NROM only supports 128 Kb or 256 Kb PRG ROM")

ASSERT(__prg_ram_size == 0 || __prg_nvram_size == 0,
       "Simulatenously using PRG-RAM and PRG-NVRAM is not supported.")

MEMORY {
  /* PRG-RAM. Not enabled by default; only used in the wild in Family BASIC. */
  prg_ram : ORIGIN = 0x6000,
            LENGTH = (__prg_ram_size + __prg_nvram_size) ?
                       64 << (__prg_ram_size + __prg_nvram_size) : 0

  /**
   * CHR-ROM LMA. Doesn't correspond to anything at runtime; this is beyond
   * 0xffff to make sure that all LMAs are unique.
   */
  chr_rom : ORIGIN = 0x10000, LENGTH = __chr_rom_size == 1 ? 0x2000 : 0

  /**
   * Note: When __prg_rom_size == 1, PRG-ROM is mirrored at 0x8000 and 0xC000.
   * Since the 6502 vectors are at 0xFFFA, using the 0xC000 mirror makes their
   * placement more obvious.
   */
  prg_rom (rx) : ORIGIN = __prg_rom_size == 2 ? 0x8000 : 0xC000,
                 LENGTH = __prg_rom_size == 2 ? 0x8000 : 0x4000
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

  .prg_ram : { *(.prg_ram .prg_ram.*) } >prg_ram

  .vector 0xfffa : { SHORT(nmi) SHORT(_start) SHORT(irq) } >prg_rom
}

INCLUDE ines.ld
