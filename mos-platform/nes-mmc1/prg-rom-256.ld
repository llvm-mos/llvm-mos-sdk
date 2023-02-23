INCLUDE _prg-rom-banked.ld

__prg_rom_size = 256;

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)     FULL(reset)
  FULL(prg_rom_1)     FULL(reset)
  FULL(prg_rom_2)     FULL(reset)
  FULL(prg_rom_3)     FULL(reset)
  FULL(prg_rom_4)     FULL(reset)
  FULL(prg_rom_5)     FULL(reset)
  FULL(prg_rom_6)     FULL(reset)
  FULL(prg_rom_7)     FULL(reset)
  FULL(prg_rom_8)     FULL(reset)
  FULL(prg_rom_9)     FULL(reset)
  FULL(prg_rom_10)    FULL(reset)
  FULL(prg_rom_11)    FULL(reset)
  FULL(prg_rom_12)    FULL(reset)
  FULL(prg_rom_13)    FULL(reset)
  FULL(prg_rom_14)    FULL(reset)
  FULL(prg_rom_fixed) FULL(reset_fixed)
  FULL(chr_rom)
}
