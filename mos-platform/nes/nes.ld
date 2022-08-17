/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

ASSERT(__prg_rom_size % 16 == 0,
       "PRG-ROM size must be evenly divisible by 16 KiB.")
ASSERT(__chr_rom_size % 8 == 0,
       "CHR-ROM size must be evenly divisible by 8 KiB.")
ASSERT(__prg_ram_size == 0 || __prg_ram_size >= 64,
       "Nonempty PRG-RAM must have at least 64 bytes.")
ASSERT(__prg_nvram_size == 0 || __prg_nvram_size >= 64,
       "Nonempty PRG-NVRAM must have at least 64 bytes.")
ASSERT(__chr_ram_size == 0 || __chr_ram_size >= 64,
       "Nonempty CHR-RAM must have at least 64 bytes.")
ASSERT(__chr_nvram_size == 0 || __chr_nvram_size >= 64,
       "Nonempty CHR-NVRAM must have at least 64 bytes.")
ASSERT(__prg_ram_size == 0 ||
       __prg_ram_size == 1 << LOG2CEIL(__prg_ram_size),
       "Nonempty PRG-RAM must be a power of 2.")
ASSERT(__prg_nvram_size == 0 ||
       __prg_nvram_size == 1 << LOG2CEIL(__prg_nvram_size),
       "Nonempty PRG-NVRAM must be a power of 2.")
ASSERT(__chr_ram_size == 0 ||
       __chr_ram_size == 1 << LOG2CEIL(__chr_ram_size),
       "Nonempty CHR-RAM must be a power of 2.")
ASSERT(__chr_nvram_size == 0 ||
       __chr_nvram_size == 1 << LOG2CEIL(__chr_nvram_size),
       "Nonempty CHR-NVRAM must be a power of 2.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* CPU address space. */
  ram : ORIGIN = 0x0200, LENGTH = 0x0600
}

SECTIONS {
  INCLUDE zp.ld
}
