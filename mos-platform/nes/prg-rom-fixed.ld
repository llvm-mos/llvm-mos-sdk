ASSERT(__prg_rom_size == 16 || __prg_rom_size == 32,
       "Fixed PRG-ROM only supports 16 KiB or 32 KiB")

__prg_rom_lma    = __prg_rom_size == 32 ? 0x8000 : 0xC000;
__prg_rom_offset = 0;

MEMORY { prg_rom (rx) : ORIGIN = __prg_rom_lma, LENGTH = __prg_rom_size * 1024 }

REGION_ALIAS("c_rom", prg_rom)

SECTIONS {
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom
}
INCLUDE dpcm.ld
SECTIONS {
  .vector 0xfffa : { SHORT(nmi) SHORT(_start) SHORT(irq) } >prg_rom
}

OUTPUT_FORMAT {
  INCLUDE ines-header.ld
  FULL(prg_rom)
  FULL(chr_rom)
}
