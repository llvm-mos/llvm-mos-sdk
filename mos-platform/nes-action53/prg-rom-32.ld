
INCLUDE _prg-rom-banked.ld

__prg_rom_size = 32;

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom_0)
  FULL(prg_rom_fixed)
  FULL(reset_stub)
  FULL(space_for_supervisor)
  FULL(vectors)
  FULL(chr_rom)
}
