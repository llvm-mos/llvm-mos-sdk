/* Watara Supervision cartridge linker script.

   Handles both unbanked 32KB cartridges and banked 64KB/128KB cartridges.
*/

PROVIDE(__cart_rom_size = 32);

ASSERT(__cart_rom_size == 1 << LOG2CEIL(__cart_rom_size),
       "__cart_rom_size must be a power of 2.")
ASSERT(__cart_rom_size >= 32,
       "__cart_rom_size must be >= 32 KiB.")
ASSERT(__cart_rom_size <= 128,
       "__cart_rom_size must be <= 128 KiB.")

/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x200, LENGTH = 0x2000 - 0x200
}

__bank0_lma = 0x01008000;
__bank1_lma = 0x01018000;
__bank2_lma = 0x01028000;
__bank3_lma = 0x01038000;
__bank4_lma = 0x01048000;
__bank5_lma = 0x01058000;
__bank6_lma = 0x01068000;

MEMORY {
  rom_0 : ORIGIN = __bank0_lma, LENGTH = __cart_rom_size >= 64 ? 0x4000 : 0
  rom_1 : ORIGIN = __bank1_lma, LENGTH = __cart_rom_size >= 64 ? 0x4000 : 0
  rom_2 : ORIGIN = __bank2_lma, LENGTH = __cart_rom_size >= 64 ? 0x4000 : 0
  rom_3 : ORIGIN = __bank3_lma, LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  rom_4 : ORIGIN = __bank4_lma, LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  rom_5 : ORIGIN = __bank5_lma, LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  rom_6 : ORIGIN = __bank6_lma, LENGTH = __cart_rom_size >= 128 ? 0x4000 : 0
  rom_fixed : ORIGIN = (__cart_rom_size >= 64 ? 0xc000 : 0x8000), LENGTH = (__cart_rom_size >= 64 ? 0x4000 : 0x8000) - 6
  vectors : ORIGIN = 0x10000 - 0x6, LENGTH = 6
}

REGION_ALIAS("c_readonly", rom_fixed)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
  .text : {
       INCLUDE text-sections.ld
       KEEP(*(.nmi_begin))
       KEEP(*(SORT_BY_INIT_PRIORITY(.nmi.* .nmi)))
       KEEP(*(.nmi_end))
  } >c_readonly
  INCLUDE rodata.ld
  INCLUDE data.ld
  INCLUDE zp.ld
  INCLUDE bss.ld
  INCLUDE noinit.ld
  
  .rom_0 : { *(.rom_0 .rom_0.*) } >rom_0
  .rom_1 : { *(.rom_1 .rom_1.*) } >rom_1
  .rom_2 : { *(.rom_2 .rom_2.*) } >rom_2
  .rom_3 : { *(.rom_3 .rom_3.*) } >rom_3
  .rom_4 : { *(.rom_4 .rom_4.*) } >rom_4
  .rom_5 : { *(.rom_5 .rom_5.*) } >rom_5
  .rom_6 : { *(.rom_6 .rom_6.*) } >rom_6
  .rom_fixed : { *(.rom_7 .rom_7.* .rom_fixed .rom_fixed.*) } >rom_fixed

  .vectors : { SHORT(nmi) SHORT(_start) SHORT(irq) } >vectors
}

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0x2000;

OUTPUT_FORMAT {
  FULL(rom_0)
  FULL(rom_1)
  FULL(rom_2)
  FULL(rom_3)
  FULL(rom_4)
  FULL(rom_5)
  FULL(rom_6)
  FULL(rom_fixed)
  FULL(vectors)
}
