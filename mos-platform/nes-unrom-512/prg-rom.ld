INCLUDE _rompoke.ld
INCLUDE _prg-rom-banked.ld

PROVIDE(__prg_rom_size = 512);

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)
  FULL(prg_rom_1)
  FULL(prg_rom_2)
  FULL(prg_rom_3)
  FULL(prg_rom_4)
  FULL(prg_rom_5)
  FULL(prg_rom_6)
  FULL(prg_rom_7)
  FULL(prg_rom_8)
  FULL(prg_rom_9)
  FULL(prg_rom_10)
  FULL(prg_rom_11)
  FULL(prg_rom_12)
  FULL(prg_rom_13)
  FULL(prg_rom_14)
  FULL(prg_rom_15)
  FULL(prg_rom_16)
  FULL(prg_rom_17)
  FULL(prg_rom_18)
  FULL(prg_rom_19)
  FULL(prg_rom_20)
  FULL(prg_rom_21)
  FULL(prg_rom_22)
  FULL(prg_rom_23)
  FULL(prg_rom_24)
  FULL(prg_rom_25)
  FULL(prg_rom_26)
  FULL(prg_rom_27)
  FULL(prg_rom_28)
  FULL(prg_rom_29)
  FULL(prg_rom_30)
  FULL(prg_rom_fixed)
  FULL(vectors)
  FULL(chr_rom)
}
