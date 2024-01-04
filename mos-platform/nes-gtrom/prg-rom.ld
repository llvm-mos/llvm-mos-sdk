INCLUDE _prg-rom-banked.ld

PROVIDE(__prg_rom_size = 512);

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(fixed, 0, __prg_rom0_fixed_size) FULL(prg_rom_0, __prg_rom0_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom1_fixed_size) FULL(prg_rom_1, __prg_rom1_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom2_fixed_size) FULL(prg_rom_2, __prg_rom2_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom3_fixed_size) FULL(prg_rom_3, __prg_rom3_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom4_fixed_size) FULL(prg_rom_4, __prg_rom4_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom5_fixed_size) FULL(prg_rom_5, __prg_rom5_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom6_fixed_size) FULL(prg_rom_6, __prg_rom6_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom7_fixed_size) FULL(prg_rom_7, __prg_rom7_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom8_fixed_size) FULL(prg_rom_8, __prg_rom8_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom9_fixed_size) FULL(prg_rom_9, __prg_rom9_fixed_size)  FULL(vectors)
  FULL(fixed, 0, __prg_rom10_fixed_size) FULL(prg_rom_10, __prg_rom10_fixed_size) FULL(vectors)
  FULL(fixed, 0, __prg_rom11_fixed_size) FULL(prg_rom_11, __prg_rom11_fixed_size) FULL(vectors)
  FULL(fixed, 0, __prg_rom12_fixed_size) FULL(prg_rom_12, __prg_rom12_fixed_size) FULL(vectors)
  FULL(fixed, 0, __prg_rom13_fixed_size) FULL(prg_rom_13, __prg_rom13_fixed_size) FULL(vectors)
  FULL(fixed, 0, __prg_rom14_fixed_size) FULL(prg_rom_14, __prg_rom14_fixed_size) FULL(vectors)
  FULL(fixed, 0, __prg_rom15_fixed_size) FULL(prg_rom_15, __prg_rom15_fixed_size) FULL(vectors)

  FULL(chr_rom)
}
