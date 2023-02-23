/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

ASSERT(__prg_rom_size == 1 << LOG2CEIL(__prg_rom_size),
       "PRG-ROM size must be a power of 2.")
ASSERT(__chr_rom_size == 0 || __chr_rom_size == 1 << LOG2CEIL(__chr_rom_size),
       "CHR-ROM size must be a power of 2.")
ASSERT(__prg_ram_size == 0 ||
       __prg_ram_size == 1 << LOG2CEIL(__prg_ram_size),
       "Nonempty PRG-RAM must be a power of 2.")
ASSERT(__prg_nvram_size == 0 ||
       __prg_nvram_size == 1 << LOG2CEIL(__prg_nvram_size),
       "Nonempty PRG-NVRAM must be a power of 2.")
ASSERT(__chr_ram_size == 0 ||
       __chr_ram_size == 1 << LOG2CEIL(__chr_ram_size),
       "Nonempty CHR-RAM must be a power of 2.")
ASSERT(__chr_nvram_size == 0 ||
       __chr_nvram_size == 1 << LOG2CEIL(__chr_nvram_size),
       "Nonempty CHR-NVRAM must be a power of 2.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* CPU address space. */
  ram : ORIGIN = 0x0200, LENGTH = 0x0600

  chr_rom : ORIGIN = 0x01000000, LENGTH = __chr_rom_size * 1024
}

SECTIONS {
  .text : {
       INCLUDE text-sections.ld
       *(.nmi_begin)
       *(SORT_BY_INIT_PRIORITY(.nmi.* .nmi))
       *(.nmi_end)
  } >c_rom
  .rodata : { INCLUDE rodata-sections.ld } >c_rom
  .data : { INCLUDE data-sections.ld } >c_ram AT>c_rom
  __data_load_start = LOADADDR(.data);
  __data_size = SIZEOF(.data);
  .zp.data : { INCLUDE zp-data-sections.ld } >zp AT>c_rom
  __zp_data_load_start = LOADADDR(.zp.data);
  __zp_data_size = SIZEOF(.zp.data);
  .zp.bss (NOLOAD) : { INCLUDE zp-bss-sections.ld } >zp
  INCLUDE zp-bss-symbols.ld
  INCLUDE zp-noinit.ld
  .bss (NOLOAD) : { INCLUDE bss-sections.ld } >c_ram
  INCLUDE bss-symbols.ld
  .noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >c_ram

  .chr_rom : { KEEP(*(.chr_rom .chr_rom.*)) } >chr_rom
}
