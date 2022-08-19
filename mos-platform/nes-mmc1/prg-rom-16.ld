__prg_rom_size = 16;

MEMORY {
  /* PRG-ROM VMA. */
  prg_rom_vma : ORIGIN = 0xc000, LENGTH = 0x4000
}

INCLUDE _prg-rom-fixed.ld
