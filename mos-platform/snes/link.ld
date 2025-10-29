/* SNES LoROM linker script for LLVM-MOS
 *
 * Multi-bank ROM for SNES LoROM mapping.
 * Target CPU: 65816 (use -mcpu=mosw65816 compiler flag)
 */

/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x0200, LENGTH = 0x1C00
    rom_bank_0 (rx)  : ORIGIN = 0x008000,  LENGTH = 0x7E00
    rom_bank_1 (rx)  : ORIGIN = 0x018000,  LENGTH = 0x7E00
    rom_bank_2 (rx)  : ORIGIN = 0x028000,  LENGTH = 0x7E00
    rom_bank_3 (rx)  : ORIGIN = 0x038000,  LENGTH = 0x7E00
    rom_bank_4 (rx)  : ORIGIN = 0x048000,  LENGTH = 0x7E00
    rom_bank_5 (rx)  : ORIGIN = 0x058000,  LENGTH = 0x7E00
    rom_bank_6 (rx)  : ORIGIN = 0x068000,  LENGTH = 0x7E00
    rom_bank_7 (rx)  : ORIGIN = 0x078000,  LENGTH = 0x7E00
    rom_bank_0_fixed : ORIGIN = 0x00FE00,  LENGTH = 0x0200
}

REGION_ALIAS("c_writeable", ram)
/* Define c_readonly for backwards compatibility, though we use classes for placement */
REGION_ALIAS("c_readonly", rom_bank_0)

/* Set initial soft stack address to just above zero page */
__stack = 0x0200;

/* Set entry point to startup code */
ENTRY(_start)

SECTIONS {
  INCLUDE c.ld
  
  /* Custom sections for ROM bank placement - these come AFTER c.ld sections */  
  
  /* Code section for rom_bank_0_fixed - placed before vectors */
  .text.rom_bank_0_fixed : { *(.text.rom_bank_0_fixed .text.rom_bank_0_fixed.*) } >rom_bank_0_fixed
  
  /* Read-only data section for rom_bank_0_fixed */
  .rodata.rom_bank_0_fixed : { *(.rodata.rom_bank_0_fixed .rodata.rom_bank_0_fixed.*) } >rom_bank_0_fixed
  
  /* Generic section for rom_bank_0_fixed (allows __attribute__((section("rom_bank_0_fixed")))) */
  rom_bank_0_fixed : { *(rom_bank_0_fixed rom_bank_0_fixed.*) } >rom_bank_0_fixed

  /* SNES Interrupt Vectors - Native Mode */
  .vectors_native 0xFFE4 : {
    SHORT(COP)        /* COP vector */
    SHORT(BRK)        /* BRK vector */
    SHORT(ABORT)      /* ABORT vector */
    SHORT(NMI)        /* NMI vector */
    SHORT(DIRQ)       /* Reserved vector */
    SHORT(IRQ)        /* IRQ vector */
    /* 4 bytes reserved */
    LONG(0x00000000)
  } >rom_bank_0_fixed
  
  /* SNES Interrupt Vectors - Emulation Mode */
  .vectors_emulation 0xFFF4 : {
    SHORT(COP)        /* COP vector */
    SHORT(DIRQ)       /* Reserved vector */
    SHORT(ABORT)      /* ABORT vector */
    SHORT(NMI)        /* NMI vector */
    SHORT(_start)     /* RESET vector - points to program entry point */
    SHORT(IRQ)        /* IRQ vector */
  } >rom_bank_0_fixed

  /* Custom sections for ROM bank placement */
  /* Code sections for specific banks */
  .text.rom_bank_0 : { *(.text.rom_bank_0 .text.rom_bank_0.*) } >rom_bank_0
  .text.rom_bank_1 : { *(.text.rom_bank_1 .text.rom_bank_1.*) } >rom_bank_1
  .text.rom_bank_2 : { *(.text.rom_bank_2 .text.rom_bank_2.*) } >rom_bank_2
  .text.rom_bank_3 : { *(.text.rom_bank_3 .text.rom_bank_3.*) } >rom_bank_3
  .text.rom_bank_4 : { *(.text.rom_bank_4 .text.rom_bank_4.*) } >rom_bank_4
  .text.rom_bank_5 : { *(.text.rom_bank_5 .text.rom_bank_5.*) } >rom_bank_5
  .text.rom_bank_6 : { *(.text.rom_bank_6 .text.rom_bank_6.*) } >rom_bank_6
  .text.rom_bank_7 : { *(.text.rom_bank_7 .text.rom_bank_7.*) } >rom_bank_7

  /* Constant/read-only data sections for specific banks */
  .rodata.rom_bank_0 : { *(.rodata.rom_bank_0 .rodata.rom_bank_0.*) } >rom_bank_0
  .rodata.rom_bank_1 : { *(.rodata.rom_bank_1 .rodata.rom_bank_1.*) } >rom_bank_1
  .rodata.rom_bank_2 : { *(.rodata.rom_bank_2 .rodata.rom_bank_2.*) } >rom_bank_2
  .rodata.rom_bank_3 : { *(.rodata.rom_bank_3 .rodata.rom_bank_3.*) } >rom_bank_3
  .rodata.rom_bank_4 : { *(.rodata.rom_bank_4 .rodata.rom_bank_4.*) } >rom_bank_4
  .rodata.rom_bank_5 : { *(.rodata.rom_bank_5 .rodata.rom_bank_5.*) } >rom_bank_5
  .rodata.rom_bank_6 : { *(.rodata.rom_bank_6 .rodata.rom_bank_6.*) } >rom_bank_6
  .rodata.rom_bank_7 : { *(.rodata.rom_bank_7 .rodata.rom_bank_7.*) } >rom_bank_7

  /* Generic sections that can be used directly with rom_bank_X names */
  /* These allow using __attribute__((section("rom_bank_0"))) directly */
  rom_bank_0 : { *(rom_bank_0 rom_bank_0.*) } >rom_bank_0
  rom_bank_1 : { *(rom_bank_1 rom_bank_1.*) } >rom_bank_1
  rom_bank_2 : { *(rom_bank_2 rom_bank_2.*) } >rom_bank_2
  rom_bank_3 : { *(rom_bank_3 rom_bank_3.*) } >rom_bank_3
  rom_bank_4 : { *(rom_bank_4 rom_bank_4.*) } >rom_bank_4
  rom_bank_5 : { *(rom_bank_5 rom_bank_5.*) } >rom_bank_5
  rom_bank_6 : { *(rom_bank_6 rom_bank_6.*) } >rom_bank_6
  rom_bank_7 : { *(rom_bank_7 rom_bank_7.*) } >rom_bank_7
}

OUTPUT_FORMAT {
 FULL(rom_bank_0)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_1)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_2)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_3)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_4)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_5)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_6)
 FULL(rom_bank_0_fixed)
 FULL(rom_bank_7)
 FULL(rom_bank_0_fixed)
}

