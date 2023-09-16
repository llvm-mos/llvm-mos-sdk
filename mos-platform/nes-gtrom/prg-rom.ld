INCLUDE _prg-rom-banked.ld

PROVIDE(__prg_rom_size = 512);

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_0, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_1, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_2, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_3, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_4, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_5, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_6, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_7, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_8, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_9, __prg_rom_fixed_size)  FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_10, __prg_rom_fixed_size) FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_11, __prg_rom_fixed_size) FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_12, __prg_rom_fixed_size) FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_13, __prg_rom_fixed_size) FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_14, __prg_rom_fixed_size) FULL(vectors)
  FULL(prg_rom_0, 0, __prg_rom_fixed_size) FULL(prg_rom_15, __prg_rom_fixed_size) FULL(vectors)
  
  FULL(chr_rom)
}
