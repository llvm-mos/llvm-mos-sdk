__prg_rom_size = 32;

MEMORY {
  /* PRG-ROM VMA. */
  prg_rom_vma : ORIGIN = 0x8000, LENGTH = 0x8000
}

INCLUDE _prg-rom-fixed.ld
