INCLUDE _prg-rom-banked.ld

__prg_rom_size = 64;

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)     FULL(reset)
  FULL(prg_rom_1)     FULL(reset)
  FULL(prg_rom_2)     FULL(reset)
  FULL(prg_rom_fixed) FULL(reset_fixed)
  FULL(chr_rom)
}
