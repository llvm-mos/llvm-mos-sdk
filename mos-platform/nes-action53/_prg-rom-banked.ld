INPUT(reset.o)

__prg_rom_0_lma     = 0x008000;
__prg_rom_1_lma     = 0x018000;
__prg_rom_2_lma     = 0x028000;
__prg_rom_fixed_lma = 0xc000;

__prg_rom_0_offset     = 0x00000;
__prg_rom_1_offset     = 0x04000;
__prg_rom_2_offset     = 0x08000;
__prg_rom_fixed_offset = __prg_rom_size * 1024 - 0x4000;

MEMORY {
  /* PRG-ROM LMAs. */
  prg_rom_0     : ORIGIN = __prg_rom_0_lma,     LENGTH = __prg_rom_size >= 32  ? 0x4000 : 0
  prg_rom_1     : ORIGIN = __prg_rom_1_lma,     LENGTH = __prg_rom_size >= 64  ? 0x4000 : 0
  prg_rom_2     : ORIGIN = __prg_rom_2_lma,     LENGTH = __prg_rom_size >= 64  ? 0x4000 : 0
  prg_rom_fixed : ORIGIN = __prg_rom_fixed_lma, LENGTH = 0x4000 - 0x20

  /* Skip over the required loader space in $ffd0-$fff9 */
  space_for_supervisor : ORIGIN = 0x10000 - 0x20, LENGTH = 0x1a
  vectors : ORIGIN = 0x10000 - 0x6, LENGTH = 6
}

REGION_ALIAS("c_readonly", prg_rom_fixed)

SECTIONS {
  .prg_rom_0     : { *(.prg_rom_0     .prg_rom_0.*)     } >prg_rom_0
  .prg_rom_1     : { *(.prg_rom_1     .prg_rom_1.*)     } >prg_rom_1
  .prg_rom_2     : { *(.prg_rom_2     .prg_rom_2.*)     } >prg_rom_2
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed
}

INCLUDE dpcm.ld

SECTIONS {
  .vectors : { KEEP(*(.vectors)) } >vectors
}
