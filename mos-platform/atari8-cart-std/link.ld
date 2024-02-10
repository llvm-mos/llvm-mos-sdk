/* Atari800 8 KiB and 16 KiB "standard" (no bank-switching) cartridge
   linker script. */

ASSERT(__cart_rom_size == 8 || __cart_rom_size == 16,
       "ATARI 800 STDCART: Only 8 KiB and 16 KiB ROM supported")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  cart_rom (rx) : ORIGIN = __cart_rom_size == 16 ? 0x8000 : 0xA000,
                  LENGTH = __cart_rom_size * 1024

  /* Memory as low as 0x700 works when not using DOS.  Assume we have
     at most 8 KiB of RAM to maximize compatabilty. */
  ram (w) : ORIGIN = 0x700, LENGTH = 0x2000 - 0x700
}

/* Provide imaginary (zero page) registers. */
__rc0 = 0x80;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x9f, "Inconsistent zero page map.")

REGION_ALIAS("c_readonly", cart_rom)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
  INCLUDE c.ld

  .cart_rom_fixed : { *(.cart_rom_fixed .cart_rom_fixed.*) } >cart_rom
  .vector 0xbffa : {
    SHORT(_start)      /* START entrypoint (after OS setup)   */
    BYTE(0x0)          /* "Inserted"                          */
    BYTE(0x04)         /* Bits: 7=diag, 2=start, 0=Enable_DOS */
    SHORT(_cart_init)  /* INIT entrpoint (before OS setup)    */
  } >cart_rom
}

OUTPUT_FORMAT { FULL(cart_rom) }
