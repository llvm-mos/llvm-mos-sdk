/* Atari Lynx .LNX linker script. */

/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

__stack = 0xc038; /* Set initial soft stack address to just above last memory address. (It grows down.) */

/* values used by asm code which we cannot calculate there */
__BOOTLDRBLOCK__   = 0x100 - (__BLOCKSIZE__ >> 8);
__BLOCK0SHIFTER__  = (__BLOCKSIZE__/1024 + 9);

__DIRECTORYSTART__ = __BOOTLDRSIZE__ + SIZEOF(.secbootldr); /* Start address of directory, exists on cart only */
__STACKSTART__     = __VIDEOSTART__ - __STACKSIZE__; /* Start (really end) address of the stack */
__CORESTART__      = __STACKSTART__ - __CORESIZE__; /* put the resident/non-banked segment right below the stack */
__CORESIZE__       = SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.rodata) + SIZEOF(.bss) + SIZEOF(.zp.data) + SIZEOF(.zp.bss); /* size of the resident/non-banked segment */
__SEGMENTSIZE__    = __CORESTART__ - __SEGMENTSTART__;  /* size of the banked segments, which is all the space from the bank start to the resident start */

PROVIDE(__SEGMENTCOUNT__ = 16);     /* Default to 16 file entries in the directory */
PROVIDE(__VIDEOSTART__   = 0xC038); /* Lynx VRAM start address, assuming no collision buffer, can be overridden */
PROVIDE(__SEGMENTSTART__ = 0x0200); /* Start address of overlay segments */
PROVIDE(__STACKSIZE__    = 0x0400); /* Assumed size of the C stack */
PROVIDE(__BLOCKSIZE__    = 0x0400); /* Cartridge block size, typically 0x0100 = 64K, 0x0200 = 128K, 0x0400 = 256K, 0x0800 = 512K */
PROVIDE(__VERSION__      = 1);      /* Version value for LNX cartridge header */
PROVIDE(__ROTATION__     = 0);      /* Rotation value for LNX cartridge header, 0 = none, 1 = left, 2 = right */

/* if no .cartnamemfr section provided, force values to pass ASSERT tests */
PROVIDE(__cartend  = 48);
PROVIDE(__cartname =  0);
PROVIDE(__cartmfr  = 32);

/* default segment start addresses */
PROVIDE(__SEGMENTSTART1__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART2__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART3__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART4__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART5__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART6__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART7__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART8__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART9__  = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART10__ = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART11__ = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART12__ = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART13__ = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART14__ = __SEGMENTSTART__);
PROVIDE(__SEGMENTSTART15__ = __SEGMENTSTART__);

/* ensure name and manufacturer are the correct lengths */
ASSERT(__cartmfr - __cartname == 32,          "Cart name must be 31 characters")
ASSERT(__cartend - __cartmfr  == 16,          "Cart manufacturer must be 15 characters")
ASSERT(__ROTATION__ >=0 && __ROTATION__ <= 2, "Invalid rotation value")
ASSERT(SIZEOF(.secbootldr) == 151,            "Secondary bootloader is not 151 bytes")
ASSERT(SIZEOF(.directory) % 8 == 0,           "Directory is not a multiple of 8 bytes")
ASSERT(SIZEOF(.segment1)  <= __SEGMENTSIZE__, "Segment 1 is larger than the available bank size")
ASSERT(SIZEOF(.segment2)  <= __SEGMENTSIZE__, "Segment 2 is larger than the available bank size")
ASSERT(SIZEOF(.segment3)  <= __SEGMENTSIZE__, "Segment 3 is larger than the available bank size")
ASSERT(SIZEOF(.segment4)  <= __SEGMENTSIZE__, "Segment 4 is larger than the available bank size")
ASSERT(SIZEOF(.segment5)  <= __SEGMENTSIZE__, "Segment 5 is larger than the available bank size")
ASSERT(SIZEOF(.segment6)  <= __SEGMENTSIZE__, "Segment 6 is larger than the available bank size")
ASSERT(SIZEOF(.segment7)  <= __SEGMENTSIZE__, "Segment 7 is larger than the available bank size")
ASSERT(SIZEOF(.segment8)  <= __SEGMENTSIZE__, "Segment 8 is larger than the available bank size")
ASSERT(SIZEOF(.segment9)  <= __SEGMENTSIZE__, "Segment 9 is larger than the available bank size")
ASSERT(SIZEOF(.segment10) <= __SEGMENTSIZE__, "Segment 10 is larger than the available bank size")
ASSERT(SIZEOF(.segment11) <= __SEGMENTSIZE__, "Segment 11 is larger than the available bank size")
ASSERT(SIZEOF(.segment12) <= __SEGMENTSIZE__, "Segment 12 is larger than the available bank size")
ASSERT(SIZEOF(.segment13) <= __SEGMENTSIZE__, "Segment 13 is larger than the available bank size")
ASSERT(SIZEOF(.segment14) <= __SEGMENTSIZE__, "Segment 14 is larger than the available bank size")
ASSERT(SIZEOF(.segment15) <= __SEGMENTSIZE__, "Segment 15 is larger than the available bank size")

MEMORY {
    lnxheader (r)  : ORIGIN = 0xFF0000,                    LENGTH = 64
    bootldr (r)  :   ORIGIN = 0xFF0100,                    LENGTH = __BOOTLDRSIZE__
    secbootldr (r) : ORIGIN = 0xfb68,                      LENGTH = SIZEOF(.secbootldr)
    directory (r)  : ORIGIN = 0xFF0200,                    LENGTH = __SEGMENTCOUNT__ * 8
    zp (rw)        : ORIGIN = __rc31 + 1,                  LENGTH = 0x100 - (__rc31 + 1)
    ram (rw)       : ORIGIN = __CORESTART__,               LENGTH = __CORESIZE__
    segment1 (rw)  : ORIGIN = __SEGMENTSTART1__ +0x010000, LENGTH = __SEGMENTSIZE__
    segment2 (rw)  : ORIGIN = __SEGMENTSTART2__ +0x020000, LENGTH = __SEGMENTSIZE__
    segment3 (rw)  : ORIGIN = __SEGMENTSTART3__ +0x030000, LENGTH = __SEGMENTSIZE__
    segment4 (rw)  : ORIGIN = __SEGMENTSTART4__ +0x040000, LENGTH = __SEGMENTSIZE__
    segment5 (rw)  : ORIGIN = __SEGMENTSTART5__ +0x050000, LENGTH = __SEGMENTSIZE__
    segment6 (rw)  : ORIGIN = __SEGMENTSTART6__ +0x060000, LENGTH = __SEGMENTSIZE__
    segment7 (rw)  : ORIGIN = __SEGMENTSTART7__ +0x070000, LENGTH = __SEGMENTSIZE__
    segment8 (rw)  : ORIGIN = __SEGMENTSTART8__ +0x080000, LENGTH = __SEGMENTSIZE__
    segment9 (rw)  : ORIGIN = __SEGMENTSTART9__ +0x090000, LENGTH = __SEGMENTSIZE__
    segment10 (rw) : ORIGIN = __SEGMENTSTART10__+0x0A0000, LENGTH = __SEGMENTSIZE__
    segment11 (rw) : ORIGIN = __SEGMENTSTART11__+0x0B0000, LENGTH = __SEGMENTSIZE__
    segment12 (rw) : ORIGIN = __SEGMENTSTART12__+0x0C0000, LENGTH = __SEGMENTSIZE__
    segment13 (rw) : ORIGIN = __SEGMENTSTART13__+0x0D0000, LENGTH = __SEGMENTSIZE__
    segment14 (rw) : ORIGIN = __SEGMENTSTART14__+0x0E0000, LENGTH = __SEGMENTSIZE__
    segment15 (rw) : ORIGIN = __SEGMENTSTART15__+0x0F0000, LENGTH = __SEGMENTSIZE__
}

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
    .lnxheader : {
        BYTE(0x4C) BYTE(0x59) BYTE(0x4E) BYTE(0x58) /* "LYNX" */
        SHORT(__BLOCKSIZE__)
        SHORT(__BLOCKSIZE__)
        SHORT(__VERSION__)
        KEEP(*(.cartnamemfr)) /* Cart name (32), manufacturer name (16) */
        BYTE(__ROTATION__) /* Rotation - 0 = None, 1 = Left, 2 = Right */
        BYTE(0x00) BYTE(0x00) BYTE(0x00) BYTE(0x00) BYTE(0x00) /* Padding */
    } >lnxheader

    .bootldr : {
        INCLUDE bootldr.ld
    } >bootldr

    .secbootldr : {
        KEEP(*(.secbootldr))
    } >secbootldr

    .directory : {
        INCLUDE directory.ld
    } >directory

    .text : {
        INCLUDE text-sections.ld
        KEEP(*(.irq_begin))
        KEEP(*(SORT_BY_INIT_PRIORITY(.irq.* .irq)))
        KEEP(*(.irq_end))
    } >c_readonly

    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE zp.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld

    .segment1  : { KEEP(*(.segment1  .segment1.*)) }  >segment1
    .segment2  : { KEEP(*(.segment2  .segment2.*)) }  >segment2
    .segment3  : { KEEP(*(.segment3  .segment3.*)) }  >segment3
    .segment4  : { KEEP(*(.segment4  .segment4.*)) }  >segment4
    .segment5  : { KEEP(*(.segment5  .segment5.*)) }  >segment5
    .segment6  : { KEEP(*(.segment6  .segment6.*)) }  >segment6
    .segment7  : { KEEP(*(.segment7  .segment7.*)) }  >segment7
    .segment8  : { KEEP(*(.segment8  .segment8.*)) }  >segment8
    .segment9  : { KEEP(*(.segment9  .segment9.*)) }  >segment9
    .segment10 : { KEEP(*(.segment10 .segment10.*)) } >segment10
    .segment11 : { KEEP(*(.segment11 .segment11.*)) } >segment11
    .segment12 : { KEEP(*(.segment12 .segment12.*)) } >segment12
    .segment13 : { KEEP(*(.segment13 .segment13.*)) } >segment13
    .segment14 : { KEEP(*(.segment14 .segment14.*)) } >segment14
    .segment15 : { KEEP(*(.segment15 .segment15.*)) } >segment15
}

OUTPUT_FORMAT {
    FULL(lnxheader)
    FULL(bootldr)
    FULL(secbootldr)
    FULL(directory)
    TRIM(ram)
    TRIM(segment1)
    TRIM(segment2)
    TRIM(segment3)
    TRIM(segment4)
    TRIM(segment5)
    TRIM(segment6)
    TRIM(segment7)
    TRIM(segment8)
    TRIM(segment9)
    TRIM(segment10)
    TRIM(segment11)
    TRIM(segment12)
    TRIM(segment13)
    TRIM(segment14)
    TRIM(segment15)
}
