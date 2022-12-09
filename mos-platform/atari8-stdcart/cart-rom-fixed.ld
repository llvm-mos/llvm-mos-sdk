ASSERT(__cart_rom_size == 8 || __cart_rom_size == 16,
       "ATARI 800 STDCART: Only 8 KiB and 16 KiB ROM supported")

MEMORY {
  cart_rom_vma (rx) : ORIGIN = __cart_rom_size == 16 ? 0x8000 : 0xA000,
                     LENGTH = __cart_rom_size * 1024
}

REGION_ALIAS("c_rom_vma", cart_rom_vma)
REGION_ALIAS("c_rom_lma", cart_rom)

SECTIONS {
  .cart_rom_fixed : { *(.cart_rom_fixed .cart_rom_fixed.*) } >cart_rom
  .vector 0xbffa - ORIGIN(cart_rom_vma) + ORIGIN(cart_rom) : {
    SHORT(_start)      /* START entrypoint (after OS setup)   */
    BYTE(0x0)          /* "Inserted"                          */
    BYTE(0x04)         /* Bits: 7=diag, 2=start, 0=Enable_DOS */
    SHORT(_cart_init)  /* INIT entrpoint (before OS setup)    */
  } >cart_rom
}
