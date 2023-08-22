INCLUDE pce-imag-regs.ld

PROVIDE(__ram_bank_size = 0x2000);
INCLUDE _rom-banked-sections.ld
REGION_ALIAS("c_rom", rom_bank0)

/* Calculate starting bank values.
 * Bank 0 is always I/O (0xFF), Bank 1 is always RAM (0xF8).
 * Banks 2 through 4 can contain additional contiguous RAM (__ram_bank_size).
 * This allows for a fixed bank of up to 48KB, or up to 24KB with all of
 * SuperGrafx RAM fixed.
 * Banks 2 through 6 can also contain more parts of the fixed ROM.
 */
__start_bank_2 = (__ram_bank_size > 0x2000) ? 0xF9 : ((__rom_bank0_size >= (6 << 13)) ? ((__rom_bank0_size >> 13) - 5) : 0x00);
__start_bank_3 = (__ram_bank_size > 0x4000) ? 0xFA : ((__rom_bank0_size >= (5 << 13)) ? ((__rom_bank0_size >> 13) - 4) : 0x00);
__start_bank_4 = (__ram_bank_size > 0x6000) ? 0xFB : ((__rom_bank0_size >= (4 << 13)) ? ((__rom_bank0_size >> 13) - 3) : 0x00);
__start_bank_5 = ((__rom_bank0_size >= (3 << 13)) ? ((__rom_bank0_size >> 13) - 2) : 0x00);
__start_bank_6 = ((__rom_bank0_size >= (2 << 13)) ? ((__rom_bank0_size >> 13) - 1) : 0x00);

MEMORY {
	zp : ORIGIN = __rc31 + 1, LENGTH = 0xf82100 - (__rc31 + 1)
	ram (rw) : ORIGIN = 0xf82200, LENGTH = __ram_bank_size - 0x200
}

REGION_ALIAS("c_ram", ram)
__stack = 0x2000 + __ram_bank_size;

INCLUDE rom-sections.ld

SECTIONS {
	.early_start : {
		. = 0xfff6 - 35;
		__early_start_start = .;
		KEEP(*(.early_start))
		__early_start_end = .;
	} >c_rom

	.vector : {
		. = 0xfff6;
		SHORT(irq_ext) SHORT(irq_vdc) SHORT(irq_timer) SHORT(nmi) SHORT(_early_start)
	} >c_rom
}

ASSERT((__early_start_end - __early_start_start) == 35, "early_start code size changed - edit link.ld to match crt0/crt0.S")
ASSERT(__early_start_end == 0xfff6, "early_start code size changed - edit link.ld to match crt0/crt0.S")
