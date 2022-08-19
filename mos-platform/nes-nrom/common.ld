/* Common elements of NES-NROM iNES file linker scripts. */

INCLUDE nes.ld

ASSERT(__chr_rom_size <= 8, "NROM only supports up to 8 KiB of CHR-ROM.")
ASSERT(__chr_rom_size == 0 || __chr_rom_size == 1 << LOG2CEIL(__chr_rom_size),
       "NROM only supports pow2 CHR-ROM sizes.")
ASSERT(__chr_ram_size + __chr_nvram_size <= 8,
       "MMC1 only supports up to 8KiB of CHR-(NV)RAM.")

ASSERT(__prg_rom_size == 16 || __prg_rom_size == 32,
       "NROM only supports 16 KiB or 32 KiB of PRG-ROM")
ASSERT(__prg_ram_size + __prg_nvram_size <= 8,
       "At most 8 KiB of PRG-(NV)RAM is supported.")

MEMORY {
  prg_ram : ORIGIN = 0x6000, LENGTH = (__prg_ram_size + __prg_nvram_size) * 1024
  prg_rom_vma (rx) : ORIGIN = __prg_rom_size == 32 ? 0x8000 : 0xC000,
                     LENGTH = __prg_rom_size * 1024
}

REGION_ALIAS("c_rom_vma", prg_rom_vma)
REGION_ALIAS("c_rom_lma", prg_rom)

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram
  .chr_rom : { KEEP(*(.chr_rom .chr_rom.*)) } >chr_rom

  .vector 0xfffa - ORIGIN(prg_rom_vma) + ORIGIN(prg_rom) : {
    SHORT(nmi) SHORT(_start) SHORT(irq)
  } >prg_rom
}

INCLUDE ines.ld
