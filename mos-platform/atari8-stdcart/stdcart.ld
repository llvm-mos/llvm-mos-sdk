/* Provide imaginary (zero page) registers. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

ASSERT(__cart_rom_size == 1 << LOG2CEIL(__cart_rom_size),
       "ATARI 800 STDCART: ROM size must be a power of 2.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* 0x700 works w/o DOS. */
  ram : ORIGIN = 0x700, LENGTH = 0x2000 - 0x700

  /* CART-ROM LMA. */
  cart_rom : ORIGIN = 0x01000000, LENGTH = __cart_rom_size * 1024
}

SECTIONS {
  .text : {
       INCLUDE text-sections.ld
  } >c_rom_vma AT>c_rom_lma
  .rodata : { INCLUDE rodata-sections.ld } >c_rom_vma AT>c_rom_lma
  .data : { INCLUDE data-sections.ld } >ram AT>c_rom_lma
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
  .bss (NOLOAD) : { INCLUDE bss-sections.ld } >ram AT>ram
  INCLUDE bss-symbols.ld
  .noinit (NOLOAD) : { INCLUDE noinit-sections.ld } >ram AT>ram
}
