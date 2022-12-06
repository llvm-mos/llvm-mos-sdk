
ASSERT(__cart_rom_size == 8 || __cart_rom_size == 16,
       "A8ROM only supports 8 KiB or 18 KiB of ROM")

MEMORY {
  cart_rom_vma (rx) : ORIGIN = __cart_rom_size == 16 ? 0x8000 : 0xA000,
                     LENGTH = __cart_rom_size * 1024
}

REGION_ALIAS("c_rom_vma", cart_rom_vma)
REGION_ALIAS("c_rom_lma", cart_rom)

SECTIONS {
  .cart_rom_fixed : { *(.cart_rom_fixed .cart_rom_fixed.*) } >cart_rom
  .vector 0xbffa - ORIGIN(cart_rom_vma) + ORIGIN(cart_rom) : {
    SHORT(_start)
    BYTE(0x0)    /* "Inserted" */
    BYTE(0x04)   /* Bits, 7=diag, 2=start, 0=Enable_DOS */
    SHORT(_fini)
  } >cart_rom
}
