/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

ASSERT(__prg_rom_size % 16 == 0,
       "PRG-ROM size must be evenly divisible by 16 KiB.")
ASSERT(__chr_rom_size % 8 == 0,
       "CHR-ROM size must be evenly divisible by 8 KiB.")
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

  /* The below LMAs were chosen such that they have a 3 bytes of addressing
   * available. The highest byte of the 32-bit LMA controls whether the address
   * is a real address (0x00), PRG-ROM LMA (0x01), CHR-ROM LMA (0x02), or PRG-RAM
   * LMA (0x03). */

  /* PRG-ROM LMA. */
  prg_rom : ORIGIN = 0x01000000, LENGTH = __prg_rom_size * 1024

  /* CHR-ROM LMA. */
  chr_rom : ORIGIN = 0x02000000, LENGTH = __chr_rom_size * 1024
}

SECTIONS {
  .text : { INCLUDE text-sections.ld } >c_rom_vma AT>c_rom_lma
  .rodata : { INCLUDE rodata-sections.ld } >c_rom_vma AT>c_rom_lma
  .data : { INCLUDE data-sections.ld } >c_ram_vma AT>c_rom_lma
  __data_load_start = LOADADDR(.data) - LOADADDR(.rodata) + ADDR(.rodata);
  __data_size = SIZEOF(.data);
  .zp.data : { INCLUDE zp-data-sections.ld } >zp AT>c_rom_lma
  __zp_data_load_start = LOADADDR(.zp.data) - LOADADDR(.rodata) + ADDR(.rodata);
  __zp_data_size = SIZEOF(.zp.data);
  /* The data initializers take up space at the C_ROM_VMA too, not just in RAM. */
  .data_initializers ADDR(.rodata) + SIZEOF(.rodata) + __data_size +
                   __zp_data_size : {} >c_rom_vma
  .zp.bss (NOLOAD) : {
    INCLUDE zp-bss-sections.ld
  } >zp
  INCLUDE zp-bss-symbols.ld
  INCLUDE zp-noinit.ld
  .bss (NOLOAD) : { INCLUDE bss-sections.ld } >c_ram_vma AT>c_ram_lma
  INCLUDE bss-symbols.ld
  .noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >c_ram_vma AT>c_ram_lma
}
