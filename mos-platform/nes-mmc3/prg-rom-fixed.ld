INPUT(reset-fixed.o)

PROVIDE(__prg_rom_size = 32);

ASSERT(__prg_rom_size <= 32, "Fixed banking supports at most 32KiB of PRG-ROM.")

MEMORY {
  prg_rom_vma : ORIGIN = 0x10000 - __prg_rom_size * 1024,
                LENGTH = __prg_rom_size * 1024
}

REGION_ALIAS("c_rom_vma", prg_rom_vma)
REGION_ALIAS("c_rom_lma", prg_rom)

INCLUDE dpcm.ld
INCLUDE _reset.ld
