__rc0 = 0xf82000;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0xf82000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0xf8201f, "Inconsistent zero page map.")

PROVIDE(__ram_bank_size = 0x2000);
INCLUDE rom-banked-sections.ld
REGION_ALIAS("c_rom", rom_vbank_0)

/* Calculate starting bank values.
 * Bank 0 is always I/O (0xFF), Bank 1 is always RAM (0xF8).
 * Banks 2 through 4 can contain additional contiguous RAM (__ram_bank_size).
 * This allows for a fixed bank of up to 48KB, or up to 24KB with all of
 * SuperGrafx RAM fixed.
 */
__start_bank_2 = (__ram_bank_size > 0x2000) ? 0xF9 : ((__rom_vbank_0_size >= (6 << 13)) ? ((__rom_vbank_0_size >> 13) - 6) : 0x00);
__start_bank_3 = (__ram_bank_size > 0x4000) ? 0xFA : ((__rom_vbank_0_size >= (5 << 13)) ? ((__rom_vbank_0_size >> 13) - 5) : 0x00);
__start_bank_4 = (__ram_bank_size > 0x6000) ? 0xFB : ((__rom_vbank_0_size >= (4 << 13)) ? ((__rom_vbank_0_size >> 13) - 4) : 0x00);
__start_bank_5 = ((__rom_vbank_0_size >= (3 << 13)) ? ((__rom_vbank_0_size >> 13) - 3) : 0x00);
__start_bank_6 = ((__rom_vbank_0_size >= (2 << 13)) ? ((__rom_vbank_0_size >> 13) - 2) : 0x00);
__start_bank_7 = ((__rom_vbank_0_size >= (1 << 13)) ? ((__rom_vbank_0_size >> 13) - 1) : 0x00);

MEMORY {
	zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
	ram (rw) : ORIGIN = 0xf82200, LENGTH = __ram_bank_size - 0x200
}

REGION_ALIAS("c_ram", ram)
__stack = 0x2000 + __ram_bank_size;

SECTIONS {
	.text : {
		INCLUDE text-sections.ld

		KEEP(*(.irq_timer_begin))
		KEEP(*(SORT_BY_INIT_PRIORITY(.irq_timer.* .irq_timer)))
		KEEP(*(.irq_timer_end))

		KEEP(*(.irq_vdc_begin))
		KEEP(*(SORT_BY_INIT_PRIORITY(.irq_vdc.* .irq_vdc)))
		KEEP(*(.irq_vdc_end))

		KEEP(*(.irq_ext_begin))
		KEEP(*(SORT_BY_INIT_PRIORITY(.irq_ext.* .irq_ext)))
		KEEP(*(.irq_ext_end))
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

	.vector : {
		. = 0xfff6;
		SHORT(irq_ext) SHORT(irq_vdc) SHORT(irq_timer) SHORT(nmi) SHORT(_start)
	} >c_rom
}
