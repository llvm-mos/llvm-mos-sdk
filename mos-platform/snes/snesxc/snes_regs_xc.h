/*
*   SNES MMIO register definitions
*/

#ifndef __SNES_REGS_H
#define __SNES_REGS_H

// For all compilers, use our custom SNES register definitions
#include "int_snes_xc.h"

// Compiler identification macro
#ifdef __WDC816CC__
#define SNES_XC_COMPILER_NAME "WDC816CC"
#elif __VBCC__
#define SNES_XC_COMPILER_NAME "VBCC816"
#elif __CC65__
#define SNES_XC_COMPILER_NAME "CC65"
#elif __TCC816__
#define SNES_XC_COMPILER_NAME "TCC816"
#elif __CALYPSI__
#define SNES_XC_COMPILER_NAME "Calypsi"
#elif __mos__
#define SNES_XC_COMPILER_NAME "LLVM-MOS"
#elif __JCC__
#define SNES_XC_COMPILER_NAME "JCC816"
#else
#define SNES_XC_COMPILER_NAME "Unknown"
#endif

// Stub malloc functions for compilers that don't support them
#ifdef __TCC816__
// TCC816 doesn't have malloc support, provide stubs
#ifndef NULL
#define NULL ((void*)0)
#endif

#endif

#ifdef __VBCC__
// VBCC816 doesn't have malloc support, provide declarations
#ifndef NULL
#define NULL ((void*)0)
#endif

// Function declarations for vbcc816 stubs
void* farMalloc(uint32_t size);
void* nearMalloc(uint32_t size);

#endif

#ifdef __CC65__
// CC65 has malloc support, include the header
#include <stdlib.h>
#include <stdio.h>

// Function declaration for cc65
void* farMalloc(uint32_t size);
#endif

#ifdef __WDC816CC__
// WDC816CC has malloc support, include the header
#include <malloc.h>
#include <stdio.h>
#endif

#ifdef __CALYPSI__
// Calypsi has malloc support, include the header
#include <stdlib.h>
#include <stdio.h>
#endif

#ifdef __mos__
// Function declaration for farmalloc stub
void* farmalloc(uint32_t size);
#endif

#ifdef __JCC__
// JCC816 doesn't have malloc support, provide declarations
#ifndef NULL
#define NULL ((void*)0)
#endif

// Function declarations for JCC816 stubs
void* farMalloc(uint32_t size);
void* nearMalloc(uint32_t size);
void free(void* ptr);
#endif

#define u8_reg(addr) (*(vu8)addr)
#define u16_reg(addr) (*(vu16)addr)
#define s8_reg(addr) (*(vs8)addr)
#define s16_reg(addr) (*(vs16)addr)
#define VRAM_ADD_TO_OBSEL_VALUE(x) (uint8_t)(((((uint16_t)(x) >> 14) & 0x07) | (((uint16_t)(x) >> 10) & 0x18)))

#define REG_INIDISP     (*(vu8)0x2100) // f--- xxxx, Force vblank and set screen brightness

//OAM registers
#define REG_OBJSEL      (*(vu8)0x2101) // sssn nbbb, s = obj size, n = name select b = name base addr>>14
#define REG_OBSEL       (*(vu8)0x2101)
#define REG_OAMADD      (*(vu16)0x2102)// OAM address pointer to 16 bits see next line
#define REG_OAMADDL     (*(vu8)0x2102) // aaaa aaaa, a = OAM address low byte
#define REG_OAMADDH     (*(vu8)0x2103) // p--- ---b, OAM address high bit and priority
/*
 Object size and tile address 
    sssnnbbb
        sss = size
        000 =  8x8  and 16x16 sprites
        001 =  8x8  and 32x32 sprites
        010 =  8x8  and 64x64 sprites
        011 = 16x16 and 32x32 sprites
        100 = 16x16 and 64x64 sprites
        101 = 32x32 and 64x64 sprites
    nn = name select, bbb = name base select
 Each sprite entry in oam is 4 bytes (+2 bits in the high table), format is:
    1 xxxx xxxx
    2 yyyy yyyy
    3 tttt tttt Note that this could also be considered as 'rrrrcccc' specifying the row and column of the tile in the 16x16 character table.
    4 hvoo pppN N = msb of tile number, p = set palette 0-7, o = priority, h/v flip
 Each byte in the high table contains settings for 4 sprites, ie 2 bits per sprite.
    first bit = X "sign" bit for x position 
    second bit = S size bit, used to determine which size to use, each sss setting in $2101 has two different sizes see above. Set to 0 for small 1 for large
 Sprite tile table in vram:
 The first table is at the address specified by the Name Base bits of $2101, and the offset of the second is determined by the Name bits of $2101.
 The word address in VRAM of a sprite's first tile may be calculated as:
 ((Base<<13) + (cccccccc<<4) + (N ? ((Name+1)<<12) : 0)) & 0x7fff
 
 Changing sprite priority sprite to sprite (not sprite to BG, see byte 4 of sprite entry for this):
 Write 1 to b to index the high table
 p can be used for rotating priority order in OAM
 step 1: set p to 1
 step 2: write the highest priority OBJ number (0-127) to $2102
 during V-blank every frame
 step 3: repeat
*/
#define REG_OAMDATA     (*(vu8)0x2104) // bbbb bbbb, OAM Data write register
// Write 1 byte at a time to OAM, changes won't take effect until a full word is written (so never write an uneven amount of bytes)

#define REG_BGMODE      (*(vu8)0x2105) // DCBA emmm, e = mode 1 bg3 prio bit, mmm = BG mode
// A/B/C/D = tile size for BG1/BG2/BG3/BG4, if set 16x16 else 8x8
#define REG_MOSAIC      (*(vu8)0x2106) // xxxx DCBA, xxxx = size, DCBA = bg 4321

//BG tile and map vram address set registers
// a = map address>>10, x = horizontal flip, y = vertical flip
#define REG_BG1SC       (*(vu8)0x2107) // aaaa aayx, 1k address boundaries
#define REG_BG2SC       (*(vu8)0x2108) // aaaa aayx $0000, $0400, $0800, $0C00, $1000 etc.
#define REG_BG3SC       (*(vu8)0x2109) // aaaa aayx
#define REG_BG4SC       (*(vu8)0x210A) // aaaa aayx
#define REG_BG12NBA     (*(vu8)0x210B) // bbbb aaaa, tile address>>12 (4k boundary), a = BG1, b = BG2
#define REG_BG34NBA     (*(vu8)0x210C) // bbbb aaaa, a = BG3, b = BG4

//BG Scroll registers
// The registers for BG1 behave differently in mode 7 from mode 0-6, see below
#define REG_M7HOFS      (*(vu8)0x210D) // \ ---x xxxx xxxx xxxx, signed 13 bit twos complement
#define REG_M7VOFS      (*(vu8)0x210E) // | ---y yyyy yyyy yyyy, signed 13 bit twos complement
#define REG_BG1HOFS     (*(vu8)0x210D) // | ---- --xx xxxx xxxx, unsigned, 10 bit x scroll
#define REG_BG1VOFS     (*(vu8)0x210E) // | ---- --yy yyyy yyyy, unsigned, 10 bit y scroll
#define REG_BG2HOFS     (*(vu8)0x210F) // | all bgs use same format as BG1 (non-mode7)
#define REG_BG2VOFS     (*(vu8)0x2110) // | 
#define REG_BG3HOFS     (*(vu8)0x2111) // |-write twice registers
#define REG_BG3VOFS     (*(vu8)0x2112) // | 
#define REG_BG4HOFS     (*(vu8)0x2113) // | 
#define REG_BG4VOFS     (*(vu8)0x2114) // / 

//VRAM registers
#define REG_VMAIN       (*(vu8)0x2115) // i--- mmaa
/* Using VMAIN:
 i = set to 0/1 for increment after writing $2118/2119
 mm = Address translation
 aa = Address increment step (0..3 = Increment Word-Address by 1,32,128,128)
    m m a a     Increment value for $2116 and $2117
    0 1 0 0     Increment by 8 (for 32 times) (4 color mode)
    1 0 0 0     Increment by 8 (for 64 times) (16 color mode)
    1 1 0 0     Increment by 8 (for 128 times) (256 color mode)
    0 0 0 0     Address Increments 1x1
    0 0 0 1     Address Increments 32x32
    0 0 1 0     Address Increments 128x128 (64x64?)
    0 0 1 1     Address Increments 128x128
 address increment > 0 (with/without translation) is useful for updating BG Map columns? (eg. after horizontal scrolling).
 $89 to write 4bpp column, $85 seems to work as well?
*/
#define REG_VMADD       (*(vu16)0x2116)// VRAM address, pointer to 16 bits
//#define REG_VMADDL      (*(vu8)0x2116) // Low byte of VRAM read/write address
//#define REG_VMADDH      (*(vu8)0x2117) // High byte of VRAM read/write address
#define REG_VMDATA      (*(vu16)0x2118)// VRAM data write, pointer to 16 bits
#define REG_VMDATAL     (*(vu8)0x2118) // Write register for low VRAM bank
#define REG_VMDATAH     (*(vu8)0x2119) // Write register for high VRAM bank
// VRAM writes are done as such: write $2118, write 2119, write 2118, write 2119 etc.

//Mode7 settings and matrix
#define REG_M7SEL       (*(vu8)0x211A) // rc-- --yx
/* Using M7SEL:
 r = When clear, the playing field is 1024x1024 pixels (so the tilemap completely fills it). When set, the playing field is much larger, and the 'empty space' fill is controlled by bit 6
 c = Empty space fill, when bit r is set: 0 = Transparent. 1 = Fill with character 0.
 x/y = Horizontal/Veritcal mirroring. If the bit is set, flip the 256x256 pixel 'screen' in that direction.

 Mode7 affine matrix, all are write twice registers
 M7A and M7B can also be used for signed multiplication.
 Write a 16 bit value to M7A and an 8 bit value to M7B and the 24 bit product
 can be read from registers $2134 to $2136 with trivial delay.
 However this is not possible during scanning in mode 7.
*/
#define REG_M7A         (*(vu8)0x211B) // \  aaaa aaaa aaaa aaaa
#define REG_M7B         (*(vu8)0x211C) // |  bbbb bbbb bbbb bbbb
#define REG_M7C         (*(vu8)0x211D) // |  you get the idea
#define REG_M7D         (*(vu8)0x211E) // | 8.8 fixed two's complement
                                        // | write twice registers
#define REG_M7X         (*(vu8)0x211F) // |  ---x xxxx xxxx xxxx 
#define REG_M7Y         (*(vu8)0x2120) // /  ---y yyyy yyyy yyyy
// M7X/Y are 13 bit two's complement signed, origin X,Y for mode7 affine transformation

//CGRAM registers
#define REG_CGADD       (*(vu8)0x2121) // cccc cccc, destination address in CGRAM for read/write
#define REG_CGDATA      (*(vu8)0x2122) // color to be written, write twice register low byte then high
// Color format is 15 bits 5x5x5 BGR as such: -bbb bbgg gggr rrrr

/* Window mask settings
 The following 3 registers have the format:
    ABCD abcd
        c/a = Enable window 1/2 for BG1/BG3/OBJ
        C/A = Enable window 1/2 for BG2/BG4/Color
        d/b = Window 1/2 Inversion for BG1/BG3/OBJ
        D/B = Window 1/2 Inversion for BG2/BG4/Color
 Example: window 2 enabled for BG1 outside and window 1 enabled for BG2 inside
 lda #%00101100
 sta $2123
*/
#define REG_W12SEL      (*(vu8)0x2123) // 
#define REG_W34SEL      (*(vu8)0x2124) // 
#define REG_WOBJSEL     (*(vu8)0x2125) // 

//Window positions, all 4 are 1 byte unsigned
#define REG_WH0         (*(vu8)0x2126) // Window 1 Left Position
#define REG_WH1         (*(vu8)0x2127) // Window 1 Right Position
#define REG_WH2         (*(vu8)0x2128) // Window 2 Left Position
#define REG_WH3         (*(vu8)0x2129) // Window 2 Right Position

//Window BG, OBJ and Color logic
//  44/33/22/11/oo/cc = Mask logic for BG1/BG2/BG3/BG4/OBJ/Color
#define REG_WBGLOG      (*(vu8)0x212A) // 4433 2211
#define REG_WOBJLOG     (*(vu8)0x212B) // ---- ccoo
#define REG_TM          (*(vu8)0x212C) // ---o 4321 layer main screen enable
#define REG_TS          (*(vu8)0x212D) // ---o 4321 layer sub screen enable
#define REG_TMW         (*(vu8)0x212E) // ---o 4321 Window Mask Designation for the Main Screen
#define REG_TSW         (*(vu8)0x212F) // ---o 4321 Window Mask Designation for the Subscreen

//Color math registers
#define REG_CGWSEL      (*(vu8)0x2130) // Color Addition Select
#define REG_CGADSUB     (*(vu8)0x2131) // Color math designation
#define REG_COLDATA     (*(vu8)0x2132) // Color for color math

//Various ppu registers, investigate further on your own if you want to know more
#define REG_SETINI      (*(vu8)0x2133) // Screen Mode/Video Select

#define REG_MPYLM       (*(vs16*)0x2134)// Mode7 A*B product, pointer to low 16 bits
#define REG_MPYMH       (*(vs16*)0x2135)// product, pointer to high 16 bits
#define REG_MPYL        (*(vu8)0x2134) // low byte
#define REG_MPYM        (*(vu8)0x2135) // mid byte
#define REG_MPYH        (*(vu8)0x2136) // high byte
#define REG_SLHV        (*(vu8)0x2137) // When read, the H/V counter (as read from $213C and $213D) will be latched to the current X and Y position if bit 7 of $4201 is set. The data actually read is open bus.
#define REG_OAMDATAREAD (*(vu8)0x2138) // 
#define REG_VMDATAREAD  (*(vu16)0x2139)// 
#define REG_VMDATALREAD (*(vu8)0x2139) // 
#define REG_VMDATAHREAD (*(vu8)0x213A) // 
#define REG_CGDATAREAD  (*(vu8)0x213B) // 
/* $2137, $213C and $213D
  Operation goes something like this:
    Read register $2137 to latch counter
    Read register twice for position (9 bits, bits 1-7 of high byte are ppu2 open bus)
    Each register ($213C, $213D) keeps seperate track of whether to return the low or high byte. The high/low selector is reset to 'low' when $213f is read (the selector is NOT reset when the counter is latched). 
    H Counter values range from 0 to 339, with 22-277 being visible on the screen. V Counter values range from 0 to 261 in NTSC mode (262 is possible every other frame when interlace is active) and 0 to 311 in PAL mode (312 in interlace?), with 1-224 (or 1-239(?) if overscan is enabled) visible on the screen.*/
#define REG_OPHCT   (*(vu8)0x213C) // ---- ---h hhhh hhhh, Horizontal scanline location
#define REG_OPVCT   (*(vu8)0x213D) // ---- ---v vvvv vvvv, Vertical scanline location

#define REG_STAT77  (*(vu8)0x213E) // trm- vvvv, OAM overflow flags
#define REG_STAT78  (*(vu8)0x213F) // fl-p vvvv, if p is 1 then PAL else NTSC

//SPC700 IO
#define REG_APUIO0  (*(vu8)0x2140) // Always write to $2140 / $2141 with 8-bit writes
#define REG_APUIO1  (*(vu8)0x2141) // 
#define REG_APUIO2  (*(vu8)0x2142) // 
#define REG_APUIO3  (*(vu8)0x2143) // 

//WRAM B-bus registers
#define REG_WMDATA  (*(vu8)0x2180) // Read/write to/from WRAM on B bus (fast access), one byte at a time
#define REG_WMADD   (*(vu16)0x2181) // WMADDL&M pointer to 16 bits
#define REG_WMADDL  (*(vu8)0x2181) // low byte of address into wram
#define REG_WMADDM  (*(vu8)0x2182) // high byte
#define REG_WMADDH  (*(vu8)0x2183) // bank byte, only one bit because there are only two banks ($7E/$7F)

#define REG_DEBUG   (*(vu8)0x21FC) //no$sns debug register, need to investigate usage

//Slow joypad access port
#define REG_JOYWR (*(vu16)0x4016) // 
#define REG_JOYA (*(vu8)0x4016) // 
#define REG_JOYB (*(vu8)0x4017) // 

//CPU internal registers
#define REG_NMITIMEN (*(vu8)0x4200) // n-vh ---a 
#define REG_WRIO    (*(vu8)0x4201) // 
// Hardware multiplication, A*B, 16 bit product in REG_RDMPY
// Both multiplication and division are unsigned (see matrix registers for signed mult)
#define REG_WRMPYA  (*(vu8)0x4202) // A
#define REG_WRMPYB  (*(vu8)0x4203) // B
// Hardware division, A/B, quotient in REG_RDDIV, remanider in REG_RDMPY
#define REG_WRDIVA  (*(vu16)0x4204) // Dividend, pointer to 16 bits
#define REG_WRDIVL  (*(vu8)0x4204) // Dividend low byte
#define REG_WRDIVH  (*(vu8)0x4205) // Dividend high byte
#define REG_WRDIVB  (*(vu8)0x4206) // Divisor

#define REG_HTIME   (*(vu16)0x4207)// pointer to 16 bits
#define REG_HTIMEL  (*(vu8)0x4207) // H-IRQ position
#define REG_HTIMEH  (*(vu8)0x4208) // msb of H-IRQ position 9 bit value
#define REG_VTIME   (*(vu16)0x4209)// pointer to 16 bit
#define REG_VTIMEL  (*(vu8)0x4209) // V-IRQ
#define REG_VTIMEH  (*(vu8)0x420A) // msb of V-IRQ scanline 9 bit value
#define REG_MDMAEN  (*(vu8)0x420B) // Enable DMA transfer on channels 7654 3210
#define REG_HDMAEN  (*(vu8)0x420C) // Enable HDMA transfer, uses same channels as DMA
#define REG_MEMSEL  (*(vu8)0x420D) // ---- ---s 0 = slow, 1 = fast rom access

#define REG_RDNMI   (*(vu8)0x4210) // read to clear NMI
#define REG_TIMEUP  (*(vu8)0x4211) // read to clear IRQ (actually important)
#define REG_HVBJOY  (*(vu8)0x4212) // vh-- ---a v=vblank h=hblank a=autojoy status
#define REG_RDIO    (*(vu8)0x4213) // ab-- ----
// a = controller 1 pin 6, b = controller 2 pin 6
// Reading this register reads data from the I/O Port.
// The way the I/O Port works, any bit set to 0 in $4201 will be 0 here.
// Any bit set to 1 in $4201 may be 1 or 0 here, depending on whether any
// other device connected to the I/O Port has set a 0 to that bit.
// Bit 'b' is connected
// to pin 6 of Controller Port 1. Bit 'a' is connected
// to pin 6 of Controller Port 2, and to the PPU Latch line.
// See register $4201 for the O side of the I/O Port

#define REG_RDDIV   (*(vu16)0x4214) // Quotient of divide, pointer to 16 bit
#define REG_RDDIVL  (*(vu8)0x4214) // qqqq qqqq, low byte of quotient
#define REG_RDDIVH  (*(vu8)0x4215) // qqqq qqqq, high byte of quotient

#define REG_RDMPY   (*(vu16)0x4216) // Product/remainder pointer to 16 bit
#define REG_RDMPYL  (*(vu8)0x4216) // Multiplication product or divide remainder low byte
#define REG_RDMPYH  (*(vu8)0x4217) // high byte

// Joypad read registers
#define JOY_R_MASK       0x10
#define JOY_L_MASK       0x20
#define JOY_X_MASK       0x40
#define JOY_A_MASK       0x80

#define JOY_RIGHT_MASK   0x01
#define JOY_LEFT_MASK    0x02
#define JOY_DOWN_MASK    0x04
#define JOY_UP_MASK      0x08
#define JOY_START_MASK   0x10
#define JOY_SELECT_MASK  0x20
#define JOY_Y_MASK       0x40
#define JOY_B_MASK       0x80

#define REG_JOY1L   (*(vu8)0x4218) // axlr0000 = A/X/L/R button status
#define REG_JOY1H   (*(vu8)0x4219) // byetUDLR = B/Y/SELECT/START/UP/DOWN/LEFT/RIGHT
#define REG_JOY2L   (*(vu8)0x421A) // 
#define REG_JOY2H   (*(vu8)0x421B) // 
#define REG_JOY3L   (*(vu8)0x421C) // 
#define REG_JOY3H   (*(vu8)0x421D) // 
#define REG_JOY4L   (*(vu8)0x421E) // 
#define REG_JOY4H   (*(vu8)0x421F) // 


//DMA/HDMA control registers
//Just use u8/16_reg(0x43xx)
//DMA0
#define REG_DMAP0        (*(vu8)0x4300) // 
#define REG_BBAD0        (*(vu8)0x4301) //
#define REG_A1T0         (*(vu16)0x4302) // 
#define REG_A1B0         (*(vu8)0x4304) //
#define REG_DAS0         (*(vu16)0x4305) //  
#define REG_DAS0L        (*(vu8)0x4305) // 
#define REG_DAS0H        (*(vu8)0x4306) // 
#define REG_DASB0        (*(vu8)0x4307) // 
#define REG_A2A0L        (*(vu8)0x4308) // 
#define REG_A2A0H        (*(vu8)0x4309) // 
#define REG_NTRL0        (*(vu8)0x430A) // 
//DMA/HDMA control registers
//Just use u8/16_reg(0x43xx)
//DMA1
#define REG_DMAP1        (*(vu8)0x4310) // 
#define REG_BBAD1        (*(vu8)0x4311) //
#define REG_A1T1         (*(vu16)0x4312) // 
#define REG_A1T1L        (*(vu8)0x4312) // 
#define REG_A1T1H        (*(vu8)0x4313) // 
#define REG_A1B1         (*(vu8)0x4314) //
#define REG_DAS1         (*(vu16)0x4315) //  
#define REG_DAS1L        (*(vu8)0x4315) // 
#define REG_DAS1H        (*(vu8)0x4316) // 
#define REG_DASB1        (*(vu8)0x4317) // 
#define REG_A2A1L        (*(vu8)0x4318) // 
#define REG_A2A1H        (*(vu8)0x4319) // 
#define REG_NTRL1        (*(vu8)0x431A) // 
//DMA2
#define REG_DMAP2        (*(vu8)0x4320) // 
#define REG_BBAD2        (*(vu8)0x4321) //
#define REG_A1T2         (*(vu16)0x4322) // 
#define REG_A1T2L        (*(vu8)0x4322) // 
#define REG_A1T2H        (*(vu8)0x4323) // 
#define REG_A1B2         (*(vu8)0x4324) //
#define REG_DAS2         (*(vu16)0x4325) //  
#define REG_DAS2L        (*(vu8)0x4325) // 
#define REG_DAS2H        (*(vu8)0x4326) // 
#define REG_DASB2        (*(vu8)0x4327) // 
#define REG_A2A2L        (*(vu8)0x4328) // 
#define REG_A2A2H        (*(vu8)0x4329) // 
#define REG_NTRL2        (*(vu8)0x432A) // 
//DMA3
#define REG_DMAP3        (*(vu8)0x4330) // 
#define REG_BBAD3        (*(vu8)0x4331) //
#define REG_A1T3         (*(vu16)0x4332) // 
#define REG_A1T3L        (*(vu8)0x4332) // 
#define REG_A1T3H        (*(vu8)0x4333) // 
#define REG_A1B3         (*(vu8)0x4334) //
#define REG_DAS3         (*(vu16)0x4335) //  
#define REG_DAS3L        (*(vu8)0x4335) // 
#define REG_DAS3H        (*(vu8)0x4336) // 
#define REG_DASB3        (*(vu8)0x4337) // 
#define REG_A2A3L        (*(vu8)0x4338) // 
#define REG_A2A3H        (*(vu8)0x4339) // 
#define REG_NTRL3        (*(vu8)0x433A) // 
//DMA4
#define REG_DMAP4        (*(vu8)0x4340) // 
#define REG_BBAD4        (*(vu8)0x4341) //
#define REG_A1T4         (*(vu16)0x4342) // 
#define REG_A1T4L        (*(vu8)0x4342) // 
#define REG_A1T4H        (*(vu8)0x4343) // 
#define REG_A1B4         (*(vu8)0x4344) //
#define REG_DAS4         (*(vu16)0x4345) //  
#define REG_DAS4L        (*(vu8)0x4345) // 
#define REG_DAS4H        (*(vu8)0x4346) // 
#define REG_DASB4        (*(vu8)0x4347) // 
#define REG_A2A4L        (*(vu8)0x4348) // 
#define REG_A2A4H        (*(vu8)0x4349) // 
#define REG_NTRL4        (*(vu8)0x434A) // 
//DMA5
#define REG_DMAP5        (*(vu8)0x4350) // 
#define REG_BBAD5        (*(vu8)0x4351) //
#define REG_A1T5         (*(vu16)0x4352) // 
#define REG_A1T5L        (*(vu8)0x4352) // 
#define REG_A1T5H        (*(vu8)0x4353) // 
#define REG_A1B5         (*(vu8)0x4354) //
#define REG_DAS5         (*(vu16)0x4355) //  
#define REG_DAS5L        (*(vu8)0x4355) // 
#define REG_DAS5H        (*(vu8)0x4356) // 
#define REG_DASB5        (*(vu8)0x4357) // 
#define REG_A2A5L        (*(vu8)0x4358) // 
#define REG_A2A5H        (*(vu8)0x4359) // 
#define REG_NTRL5        (*(vu8)0x435A) // 
//DMA6
#define REG_DMAP6        (*(vu8)0x4360) // 
#define REG_BBAD6        (*(vu8)0x4361) //
#define REG_A1T6         (*(vu16)0x4362) // 
#define REG_A1T6L        (*(vu8)0x4362) // 
#define REG_A1T6H        (*(vu8)0x4363) // 
#define REG_A1B6         (*(vu8)0x4364) //
#define REG_DAS6         (*(vu16)0x4365) //  
#define REG_DAS6L        (*(vu8)0x4365) // 
#define REG_DAS6H        (*(vu8)0x4366) // 
#define REG_DASB6        (*(vu8)0x4367) // 
#define REG_A2A6L        (*(vu8)0x4368) // 
#define REG_A2A6H        (*(vu8)0x4369) // 
#define REG_NTRL6        (*(vu8)0x436A) // 
//DMA7
#define REG_DMAP7        (*(vu8)0x4370) // 
#define REG_BBAD7        (*(vu8)0x4371) //
#define REG_A1T7         (*(vu16)0x4372) // 
#define REG_A1T7L        (*(vu8)0x4372) // 
#define REG_A1T7H        (*(vu8)0x4373) // 
#define REG_A1B7         (*(vu8)0x4374) //
#define REG_DAS7         (*(vu16)0x4375) //  
#define REG_DAS7L        (*(vu8)0x4375) // 
#define REG_DAS7H        (*(vu8)0x4376) // 
#define REG_DASB7        (*(vu8)0x4377) // 
#define REG_A2A7L        (*(vu8)0x4378) // 
#define REG_A2A7H        (*(vu8)0x4379) // 
#define REG_NTRL7        (*(vu8)0x437A) // 




/*  <---Registers used for DMA--->
 DMA transfers take 8 master cycles per byte transferred, no matter the FastROM setting.
 There is also an overhead of 8 master cycles per channel, and an overhead of 12-24 cycles for the whole transfer.
DMA Control Register            $43x0 ; d--i fttt
    d = Transfer direction, 0 = A bus to B bus, 1 = B to A.
    i = Address increment, 0 = increment DMA address for each byte. 1 = decrement
    f = DMA fixed transfer
        0 = source address will be adjusted as specified by bit 4
        1 = source address will not be adjusted
    t = How data is written/read, see table below (dest = byte in $43x1):
    000 => 1 register write once             (1 byte:  p               )
    001 => 2 registers write once            (2 bytes: p, p+1          )
    010 => 1 register write twice            (2 bytes: p, p            )
    011 => 2 registers write twice each      (4 bytes: p, p,   p+1, p+1)
    100 => 4 registers write once            (4 bytes: p, p+1, p+2, p+3)
    101 => 2 registers write twice alternate (4 bytes: p, p+1, p,   p+1)
    110 => 1 register write twice            (2 bytes: p, p            )
    111 => 2 registers write twice each      (4 bytes: p, p,   p+1, p+1)

DMA Destination             $43x1 ; aaaa aaaa
    a = Destination register for DMA write on address bus B ($21xx)

DMA Source Address (Low)        $43x2 ; llll llll
DMA Source Address (High)       $43x3 ; hhhh hhhh
DMA Source Bank             $43x4 ; bbbb bbbb
    bhl = bank:address for the source on A bus in DMA transfer (eg. $80BEEF)

DMA Transfer Size (Low)     $43x5 ; llll llll
DMA Transfer Size (High)        $43x6 ; hhhh hhhh
 Size of the transfer, 2 bytes ($0000 = 64k transfer,$8000 = 32k transfer)


    <---Registers used for HDMA--->
 HDMA overhead is ~18 master cycles, plus 8 master cycles for each channel set for direct HDMA and 24 master cycles for each channel set for indirect HDMA.

HDMA Control Register           $43x0 ; da-- -ttt
    d and t are same as DMA
    a = Set to 1 for indirect addressing, 0 for direct.

HDMA Destination                $43x1 ; aaaa aaaa
    a = same as DMA
HDMA Table Address (Low)        $43x2 ; llll llll
HDMA Table Address (High)       $43x3 ; hhhh hhhh
HDMA Table Bank             $43x4 ; bbbb bbbb
    bhl = same as DMA

HDMA Indirect Address (Low) $43x5 ; llll llll
HDMA Indirect Address (High)    $43x6 ; hhhh hhhh
HDMA Indirect Bank              $43x7 ; bbbb bbbb
    bhl = bank:address for indirect HDMA (eg. $7EFACE)
    You only need to set the bank byte for indirect HDMA.
    The resulting bank:address is the pointer used in the HDMA transfer.

HDMA Mid Frame Table Address (Low) $43x8 ; aaaa aaaa, 
HDMA Mid Frame Table Address (High)$43x9 ; aaaa aaaa, 
    At the beginning of the frame $43x2/3 are copied into $43x8/9 registers for all active HDMA channels,
    and then this register is updated as the table is read.

HDMA Line Counter Register          $43xA ; rccc cccc, r = Repeat, c = Line count
    About $43xA:
    The register is decremeted before being checked for r status or c==0.
    Thus, setting a value of $80 is really "128 lines with no repeat" rather than "0 lines with repeat".
    Similarly, a value of $00 will be "128 lines with repeat" when it doesn't mean "terminate the channel"(assuming this can only happen if you manually write $43xA?).
    This register is initialized at the end of V-Blank for every active HDMA channel.
    Note that if a game wishes to begin HDMA during the frame, it will most likely have to initalize this register.
*/


// SA-1 registers

// $2200 - SA-1 CPU Control
#define SA1_CCNT      (*(vu8)0x2200)
// $2201 - SNES CPU Interrupt Enable
#define SA1_SIE       (*(vu8)0x2201)
// $2202 - SNES CPU Interrupt Clear
#define SA1_SIC       (*(vu8)0x2202)
// $2203/$2204 - SA-1 CPU Reset Vector (2 bytes)
#define SA1_CRV       (*(vu16)0x2203)
// $2205/$2206 - SA-1 CPU NMI Vector (2 bytes)
#define SA1_CNV       (*(vu16)0x2205)
// $2207/$2208 - SA-1 CPU IRQ Vector (2 bytes)
#define SA1_CIV       (*(vu16)0x2207)
// $2209 - SNES CPU Control
#define SA1_SCNT      (*(vu8)0x2209)
// $220A - SA-1 CPU Interrupt Enable
#define SA1_CIE       (*(vu8)0x220A)
// $220B - SA-1 CPU Interrupt Clear
#define SA1_CIC       (*(vu8)0x220B)
// $220C/$220D - SNES CPU NMI Vector (2 bytes)
#define SA1_SNV       (*(vu16)0x220C)
// $220E/$220F - SNES CPU IRQ Vector (2 bytes)
#define SA1_SIV       (*(vu16)0x220E)
// $2210 - H/V Timer Control
#define SA1_TMC       (*(vu8)0x2210)
// $2211 - SA-1 CPU Timer Restart
#define SA1_CTR       (*(vu8)0x2211)
// $2212/$2213 - Set H-Count (2 bytes)
#define SA1_HCNT      (*(vu16)0x2212)
// $2214/$2215 - Set V-Count (2 bytes)
#define SA1_VCNT      (*(vu16)0x2214)
// $2220 - Set Super MMC Bank C
#define SA1_CXB       (*(vu8)0x2220)
// $2221 - Set Super MMC Bank D
#define SA1_DXB       (*(vu8)0x2221)
// $2222 - Set Super MMC Bank E
#define SA1_EXB       (*(vu8)0x2222)
// $2223 - Set Super MMC Bank F
#define SA1_FXB       (*(vu8)0x2223)
// $2224 - SNES CPU BW-RAM Address Mapping
#define SA1_BMAPS     (*(vu8)0x2224)
// $2225 - SA-1 CPU BW-RAM Address Mapping
#define SA1_BMAP      (*(vu8)0x2225)
// $2226 - SNES CPU BW-RAM Write Enable
#define SA1_SBWE      (*(vu8)0x2226)
// $2227 - SA-1 CPU BW-RAM Write Enable
#define SA1_CBWE      (*(vu8)0x2227)
// $2228 - BW-RAM Write-Protected Area
#define SA1_BPWA      (*(vu8)0x2228)
// $2229 - SA-1 I-RAM Write Protection
#define SA1_SIWP      (*(vu8)0x2229)
// $222A - SA-1 I-RAM Write Protection
#define SA1_CIWP      (*(vu8)0x222A)
// $2230 - DMA Control
#define SA1_DCNT      (*(vu8)0x2230)
// $2231 - Character Conversion OMA Parameters
#define SA1_CDMA      (*(vu8)0x2231)
// $2232/$2233/$2234 - DMA Source Device Start Address (3 bytes)
#define SA1_SDA       ((vu8)0x2232) // Use as array: [0]=low, [1]=mid, [2]=high
// $2235/$2236/$2237 - DMA Destination Start Address (3 bytes)
#define SA1_DDA       ((vu8)0x2235) // Use as array: [0]=low, [1]=mid, [2]=high
// $2238/$2239 - DMA Terminal Counter (2 bytes)
#define SA1_DTC       (*(vu16)0x2238)
// $223F - BW-RAM Bit Map Format
#define SA1_BBF       (*(vu8)0x223F)
// $2240-$224F - Bit Map Register File (16 bytes)
#define SA1_BRF       ((vu8)0x2240) // Use as array: [0]...[15]
// $2250 - Arithmetic Control
#define SA1_MCNT      (*(vu8)0x2250)
// $2251/$2252 - Arithmetic Parameters: Multiplicand/Dividend (2 bytes)
#define SA1_MA        (*(vu16)0x2251)
// $2253/$2254 - Arithmetic Parameters: Multiplier/Divisor (2 bytes)
#define SA1_MB        (*(vu16)0x2253)
// $2258 - Variable-Length Bit Processing
#define SA1_VBD       (*(vu8)0x2258)
// $2259/$225A/$225B - Variable-Length Bit Game Pak ROM Start Address (3 bytes)
#define SA1_VDA       ((vu8)0x2259) // Use as array: [0]=low, [1]=mid, [2]=high



// MSU1 Register Definitions
#define MSU1_STATUS     (*(volatile uint8_t*)0x2000)
#define MSU1_DATA       (*(volatile uint8_t*)0x2001)
#define MSU1_IDENT      (*(volatile uint8_t*)0x2002)
#define MSU1_OFFSET     (*(volatile uint32_t*)0x2000)
#define MSU1_TRACK      (*(volatile uint16_t*)0x2004)
#define MSU1_VOLUME     (*(volatile uint8_t*)0x2006)
#define MSU1_CONTROL    (*(volatile uint8_t*)0x2007)

// MSU1 Status Bits
#define MSU1_STATUS_DATA_BUSY    (1 << 7)
#define MSU1_STATUS_AUDIO_BUSY  (1 << 6)
#define MSU1_STATUS_AUDIO_REPEAT (1 << 5)
#define MSU1_STATUS_AUDIO_PLAY  (1 << 4)

// MSU1 Control Bits
#define MSU1_CONTROL_PLAY       (1 << 0)
#define MSU1_CONTROL_REPEAT     (1 << 1)


//A union structure for OAM duplicates so the compiler creates less warnings.
//Table 2 consists of 2 32 bytes with 2 bit entries
//Fist bit is the X flag
//Second bit is the size flag



union uOAMCopy{
    unsigned char Bytes[544];
    struct tagstOAMCopy{
        uint8_t OBJ000X;
        uint8_t OBJ000Y;
        uint8_t CHARNUM000;
        uint8_t PROPERTIES000;
        uint8_t OBJ001X;
        uint8_t OBJ001Y;
        uint8_t CHARNUM001;
        uint8_t PROPERTIES001;
        uint8_t OBJ002X;
        uint8_t OBJ002Y;
        uint8_t CHARNUM002;
        uint8_t PROPERTIES002;
        uint8_t OBJ003X;
        uint8_t OBJ003Y;
        uint8_t CHARNUM003;
        uint8_t PROPERTIES003;
        uint8_t OBJ004X;
        uint8_t OBJ004Y;
        uint8_t CHARNUM004;
        uint8_t PROPERTIES004;
        uint8_t OBJ005X;
        uint8_t OBJ005Y;
        uint8_t CHARNUM005;
        uint8_t PROPERTIES005;
        uint8_t OBJ006X;
        uint8_t OBJ006Y;
        uint8_t CHARNUM006;
        uint8_t PROPERTIES006;
        uint8_t OBJ007X;
        uint8_t OBJ007Y;
        uint8_t CHARNUM007;
        uint8_t PROPERTIES007;
        uint8_t OBJ008X;
        uint8_t OBJ008Y;
        uint8_t CHARNUM008;
        uint8_t PROPERTIES008;
        uint8_t OBJ009X;
        uint8_t OBJ009Y;
        uint8_t CHARNUM009;
        uint8_t PROPERTIES009;
        uint8_t OBJ010X;
        uint8_t OBJ010Y;
        uint8_t CHARNUM010;
        uint8_t PROPERTIES010;
        uint8_t OBJ011X;
        uint8_t OBJ011Y;
        uint8_t CHARNUM011;
        uint8_t PROPERTIES011;
        uint8_t OBJ012X;
        uint8_t OBJ012Y;
        uint8_t CHARNUM012;
        uint8_t PROPERTIES012;
        uint8_t OBJ013X;
        uint8_t OBJ013Y;
        uint8_t CHARNUM013;
        uint8_t PROPERTIES013;
        uint8_t OBJ014X;
        uint8_t OBJ014Y;
        uint8_t CHARNUM014;
        uint8_t PROPERTIES014;
        uint8_t OBJ015X;
        uint8_t OBJ015Y;
        uint8_t CHARNUM015;
        uint8_t PROPERTIES015;
        uint8_t OBJ016X;
        uint8_t OBJ016Y;
        uint8_t CHARNUM016;
        uint8_t PROPERTIES016;
        uint8_t OBJ017X;
        uint8_t OBJ07Y;
        uint8_t CHARNUM017;
        uint8_t PROPERTIES017;
        uint8_t OBJ018X;
        uint8_t OBJ018Y;
        uint8_t CHARNUM018;
        uint8_t PROPERTIES018;
        uint8_t OBJ019X;
        uint8_t OBJ019Y;
        uint8_t CHARNUM019;
        uint8_t PROPERTIES019;
        uint8_t OBJ020X;
        uint8_t OBJ020Y;
        uint8_t CHARNUM020;
        uint8_t PROPERTIES020;
        uint8_t OBJ021X;
        uint8_t OBJ021Y;
        uint8_t CHARNUM021;
        uint8_t PROPERTIES021;
        uint8_t OBJ022X;
        uint8_t OBJ022Y;
        uint8_t CHARNUM022;
        uint8_t PROPERTIES022;
        uint8_t OBJ023X;
        uint8_t OBJ023Y;
        uint8_t CHARNUM023;
        uint8_t PROPERTIES023;
        uint8_t OBJ0024X;
        uint8_t OBJ024Y;
        uint8_t CHARNUM024;
        uint8_t PROPERTIES024;
        uint8_t OBJ025X;
        uint8_t OBJ025Y;
        uint8_t CHARNUM025;
        uint8_t PROPERTIES025;
        uint8_t OBJ026X;
        uint8_t OBJ026Y;
        uint8_t CHARNUM026;
        uint8_t PROPERTIES026;
        uint8_t OBJ027X;
        uint8_t OBJ027Y;
        uint8_t CHARNUM027;
        uint8_t PROPERTIES027;
        uint8_t OBJ028X;
        uint8_t OBJ028Y;
        uint8_t CHARNUM028;
        uint8_t PROPERTIES028;
        uint8_t OBJ029X;
        uint8_t OBJ029Y;
        uint8_t CHARNUM029;
        uint8_t PROPERTIES029;
        uint8_t OBJ030X;
        uint8_t OBJ030Y;
        uint8_t CHARNUM030;
        uint8_t PROPERTIES030;
        uint8_t OBJ031X;
        uint8_t OBJ031Y;
        uint8_t CHARNUM031;
        uint8_t PROPERTIES031;
        uint8_t OBJ032X;
        uint8_t OBJ032Y;
        uint8_t CHARNUM032;
        uint8_t PROPERTIES032;
        uint8_t OBJ033X;
        uint8_t OBJ033Y;
        uint8_t CHARNUM033;
        uint8_t PROPERTIES033;
        uint8_t OBJ0034X;
        uint8_t OBJ034Y;
        uint8_t CHARNUM034;
        uint8_t PROPERTIES034;
        uint8_t OBJ035X;
        uint8_t OBJ035Y;
        uint8_t CHARNUM035;
        uint8_t PROPERTIES035;
        uint8_t OBJ036X;
        uint8_t OBJ036Y;
        uint8_t CHARNUM036;
        uint8_t PROPERTIES036;
        uint8_t OBJ037X;
        uint8_t OBJ037Y;
        uint8_t CHARNUM037;
        uint8_t PROPERTIES037;
        uint8_t OBJ038X;
        uint8_t OBJ038Y;
        uint8_t CHARNUM038;
        uint8_t PROPERTIES038;
        uint8_t OBJ039X;
        uint8_t OBJ039Y;
        uint8_t CHARNUM039;
        uint8_t PROPERTIES039;
        uint8_t OBJ040X;
        uint8_t OBJ040Y;
        uint8_t CHARNUM040;
        uint8_t PROPERTIES040;
        uint8_t OBJ041X;
        uint8_t OBJ041Y;
        uint8_t CHARNUM041;
        uint8_t PROPERTIES041;
        uint8_t OBJ042X;
        uint8_t OBJ042Y;
        uint8_t CHARNUM042;
        uint8_t PROPERTIES042;
        uint8_t OBJ043X;
        uint8_t OBJ043Y;
        uint8_t CHARNUM043;
        uint8_t PROPERTIES043;
        uint8_t OBJ0044X;
        uint8_t OBJ044Y;
        uint8_t CHARNUM044;
        uint8_t PROPERTIES044;
        uint8_t OBJ045X;
        uint8_t OBJ045Y;
        uint8_t CHARNUM045;
        uint8_t PROPERTIES045;
        uint8_t OBJ046X;
        uint8_t OBJ046Y;
        uint8_t CHARNUM046;
        uint8_t PROPERTIES046;
        uint8_t OBJ047X;
        uint8_t OBJ047Y;
        uint8_t CHARNUM047;
        uint8_t PROPERTIES047;
        uint8_t OBJ048X;
        uint8_t OBJ048Y;
        uint8_t CHARNUM048;
        uint8_t PROPERTIES048;
        uint8_t OBJ049X;
        uint8_t OBJ049Y;
        uint8_t CHARNUM049;
        uint8_t PROPERTIES049;
        uint8_t OBJ050X;
        uint8_t OBJ050Y;
        uint8_t CHARNUM050;
        uint8_t PROPERTIES050;
        uint8_t OBJ051X;
        uint8_t OBJ051Y;
        uint8_t CHARNUM051;
        uint8_t PROPERTIES051;
        uint8_t OBJ052X;
        uint8_t OBJ052Y;
        uint8_t CHARNUM052;
        uint8_t PROPERTIES052;
        uint8_t OBJ053X;
        uint8_t OBJ053Y;
        uint8_t CHARNUM053;
        uint8_t PROPERTIES053;
        uint8_t OBJ0054X;
        uint8_t OBJ054Y;
        uint8_t CHARNUM054;
        uint8_t PROPERTIES054;
        uint8_t OBJ055X;
        uint8_t OBJ055Y;
        uint8_t CHARNUM055;
        uint8_t PROPERTIES055;
        uint8_t OBJ056X;
        uint8_t OBJ056Y;
        uint8_t CHARNUM056;
        uint8_t PROPERTIES056;
        uint8_t OBJ057X;
        uint8_t OBJ057Y;
        uint8_t CHARNUM057;
        uint8_t PROPERTIES057;
        uint8_t OBJ058X;
        uint8_t OBJ058Y;
        uint8_t CHARNUM058;
        uint8_t PROPERTIES058;
        uint8_t OBJ059X;
        uint8_t OBJ059Y;
        uint8_t CHARNUM059;
        uint8_t PROPERTIES059;
        uint8_t OBJ060X;
        uint8_t OBJ060Y;
        uint8_t CHARNUM060;
        uint8_t PROPERTIES060;
        uint8_t OBJ061X;
        uint8_t OBJ061Y;
        uint8_t CHARNUM061;
        uint8_t PROPERTIES061;
        uint8_t OBJ062X;
        uint8_t OBJ062Y;
        uint8_t CHARNUM062;
        uint8_t PROPERTIES062;
        uint8_t OBJ063X;
        uint8_t OBJ063Y;
        uint8_t CHARNUM063;
        uint8_t PROPERTIES063;
        uint8_t OBJ0064X;
        uint8_t OBJ064Y;
        uint8_t CHARNUM064;
        uint8_t PROPERTIES064;
        uint8_t OBJ065X;
        uint8_t OBJ065Y;
        uint8_t CHARNUM065;
        uint8_t PROPERTIES065;
        uint8_t OBJ066X;
        uint8_t OBJ066Y;
        uint8_t CHARNUM066;
        uint8_t PROPERTIES066;
        uint8_t OBJ067X;
        uint8_t OBJ067Y;
        uint8_t CHARNUM067;
        uint8_t PROPERTIES067;
        uint8_t OBJ068X;
        uint8_t OBJ068Y;
        uint8_t CHARNUM068;
        uint8_t PROPERTIES068;
        uint8_t OBJ069X;
        uint8_t OBJ069Y;
        uint8_t CHARNUM069;
        uint8_t PROPERTIES069;
        uint8_t OBJ070X;
        uint8_t OBJ070Y;
        uint8_t CHARNUM070;
        uint8_t PROPERTIES070;
        uint8_t OBJ071X;
        uint8_t OBJ071Y;
        uint8_t CHARNUM071;
        uint8_t PROPERTIES071;
        uint8_t OBJ072X;
        uint8_t OBJ072Y;
        uint8_t CHARNUM072;
        uint8_t PROPERTIES072;
        uint8_t OBJ073X;
        uint8_t OBJ073Y;
        uint8_t CHARNUM073;
        uint8_t PROPERTIES073;
        uint8_t OBJ0074X;
        uint8_t OBJ074Y;
        uint8_t CHARNUM074;
        uint8_t PROPERTIES074;
        uint8_t OBJ075X;
        uint8_t OBJ075Y;
        uint8_t CHARNUM075;
        uint8_t PROPERTIES075;
        uint8_t OBJ076X;
        uint8_t OBJ076Y;
        uint8_t CHARNUM076;
        uint8_t PROPERTIES076;
        uint8_t OBJ077X;
        uint8_t OBJ077Y;
        uint8_t CHARNUM077;
        uint8_t PROPERTIES077;
        uint8_t OBJ078X;
        uint8_t OBJ078Y;
        uint8_t CHARNUM078;
        uint8_t PROPERTIES078;
        uint8_t OBJ079X;
        uint8_t OBJ079Y;
        uint8_t CHARNUM079;
        uint8_t PROPERTIES079;
        uint8_t OBJ080X;
        uint8_t OBJ080Y;
        uint8_t CHARNUM080;
        uint8_t PROPERTIES080;
        uint8_t OBJ081X;
        uint8_t OBJ081Y;
        uint8_t CHARNUM081;
        uint8_t PROPERTIES081;
        uint8_t OBJ082X;
        uint8_t OBJ082Y;
        uint8_t CHARNUM082;
        uint8_t PROPERTIES082;
        uint8_t OBJ083X;
        uint8_t OBJ083Y;
        uint8_t CHARNUM083;
        uint8_t PROPERTIES083;
        uint8_t OBJ0084X;
        uint8_t OBJ084Y;
        uint8_t CHARNUM084;
        uint8_t PROPERTIES084;
        uint8_t OBJ085X;
        uint8_t OBJ085Y;
        uint8_t CHARNUM085;
        uint8_t PROPERTIES085;
        uint8_t OBJ086X;
        uint8_t OBJ086Y;
        uint8_t CHARNUM086;
        uint8_t PROPERTIES086;
        uint8_t OBJ087X;
        uint8_t OBJ087Y;
        uint8_t CHARNUM087;
        uint8_t PROPERTIES087;
        uint8_t OBJ088X;
        uint8_t OBJ088Y;
        uint8_t CHARNUM088;
        uint8_t PROPERTIES088;
        uint8_t OBJ089X;
        uint8_t OBJ089Y;
        uint8_t CHARNUM089;
        uint8_t PROPERTIES089;
        uint8_t OBJ090X;
        uint8_t OBJ090Y;
        uint8_t CHARNUM090;
        uint8_t PROPERTIES090;
        uint8_t OBJ091X;
        uint8_t OBJ091Y;
        uint8_t CHARNUM091;
        uint8_t PROPERTIES091;
        uint8_t OBJ092X;
        uint8_t OBJ092Y;
        uint8_t CHARNUM092;
        uint8_t PROPERTIES092;
        uint8_t OBJ093X;
        uint8_t OBJ093Y;
        uint8_t CHARNUM093;
        uint8_t PROPERTIES093;
        uint8_t OBJ0094X;
        uint8_t OBJ094Y;
        uint8_t CHARNUM094;
        uint8_t PROPERTIES094;
        uint8_t OBJ095X;
        uint8_t OBJ095Y;
        uint8_t CHARNUM095;
        uint8_t PROPERTIES095;
        uint8_t OBJ096X;
        uint8_t OBJ096Y;
        uint8_t CHARNUM096;
        uint8_t PROPERTIES096;
        uint8_t OBJ097X;
        uint8_t OBJ097Y;
        uint8_t CHARNUM097;
        uint8_t PROPERTIES097;
        uint8_t OBJ098X;
        uint8_t OBJ098Y;
        uint8_t CHARNUM098;
        uint8_t PROPERTIES098;
        uint8_t OBJ099X;
        uint8_t OBJ099Y;
        uint8_t CHARNUM099;
        uint8_t PROPERTIES099;
        uint8_t OBJ100X;
        uint8_t OBJ100Y;
        uint8_t CHARNUM100;
        uint8_t PROPERTIES100;
        uint8_t OBJ101X;
        uint8_t OBJ101Y;
        uint8_t CHARNUM101;
        uint8_t PROPERTIES101;
        uint8_t OBJ102X;
        uint8_t OBJ102Y;
        uint8_t CHARNUM102;
        uint8_t PROPERTIES102;
        uint8_t OBJ103X;
        uint8_t OBJ103Y;
        uint8_t CHARNUM103;
        uint8_t PROPERTIES103;
        uint8_t OBJ104X;
        uint8_t OBJ104Y;
        uint8_t CHARNUM104;
        uint8_t PROPERTIES104;
        uint8_t OBJ105X;
        uint8_t OBJ105Y;
        uint8_t CHARNUM105;
        uint8_t PROPERTIES105;
        uint8_t OBJ106X;
        uint8_t OBJ106Y;
        uint8_t CHARNUM106;
        uint8_t PROPERTIES106;
        uint8_t OBJ107X;
        uint8_t OBJ107Y;
        uint8_t CHARNUM107;
        uint8_t PROPERTIES107;
        uint8_t OBJ108X;
        uint8_t OBJ108Y;
        uint8_t CHARNUM108;
        uint8_t PROPERTIES108;
        uint8_t OBJ109X;
        uint8_t OBJ109Y;
        uint8_t CHARNUM109;
        uint8_t PROPERTIES109;
        uint8_t OBJ110X;
        uint8_t OBJ110Y;
        uint8_t CHARNUM110;
        uint8_t PROPERTIES110;
        uint8_t OBJ111X;
        uint8_t OBJ111Y;
        uint8_t CHARNUM111;
        uint8_t PROPERTIES111;
        uint8_t OBJ112X;
        uint8_t OBJ112Y;
        uint8_t CHARNUM112;
        uint8_t PROPERTIES112;
        uint8_t OBJ113X;
        uint8_t OBJ113Y;
        uint8_t CHARNUM113;
        uint8_t PROPERTIES113;
        uint8_t OBJ114X;
        uint8_t OBJ114Y;
        uint8_t CHARNUM114;
        uint8_t PROPERTIES114;
        uint8_t OBJ115X;
        uint8_t OBJ115Y;
        uint8_t CHARNUM115;
        uint8_t PROPERTIES115;
        uint8_t OBJ116X;
        uint8_t OBJ116Y;
        uint8_t CHARNUM116;
        uint8_t PROPERTIES116;
        uint8_t OBJ117X;
        uint8_t OBJ117Y;
        uint8_t CHARNUM117;
        uint8_t PROPERTIES117;
        uint8_t OBJ118X;
        uint8_t OBJ118Y;
        uint8_t CHARNUM118;
        uint8_t PROPERTIES118;
        uint8_t OBJ119X;
        uint8_t OBJ119Y;
        uint8_t CHARNUM119;
        uint8_t PROPERTIES119;
        uint8_t OBJ120X;
        uint8_t OBJ120Y;
        uint8_t CHARNUM120;
        uint8_t PROPERTIES120;
        uint8_t OBJ121X;
        uint8_t OBJ121Y;
        uint8_t CHARNUM121;
        uint8_t PROPERTIES121;
        uint8_t OBJ122X;
        uint8_t OBJ122Y;
        uint8_t CHARNUM122;
        uint8_t PROPERTIES122;
        uint8_t OBJ123X;
        uint8_t OBJ123Y;
        uint8_t CHARNUM123;
        uint8_t PROPERTIES123;
        uint8_t OBJ124X;
        uint8_t OBJ124Y;
        uint8_t CHARNUM124;
        uint8_t PROPERTIES124;
        uint8_t OBJ125X;
        uint8_t OBJ125Y;
        uint8_t CHARNUM125;
        uint8_t PROPERTIES125;
        uint8_t OBJ126X;
        uint8_t OBJ126Y;
        uint8_t CHARNUM126;
        uint8_t PROPERTIES126;
        uint8_t OBJ127X;
        uint8_t OBJ127Y;
        uint8_t CHARNUM127;
        uint8_t PROPERTIES127;
        uint8_t OAMTABLE2BYTE00;
        uint8_t OAMTABLE2BYTE01;
        uint8_t OAMTABLE2BYTE02;
        uint8_t OAMTABLE2BYTE03;
        uint8_t OAMTABLE2BYTE04;
        uint8_t OAMTABLE2BYTE05;
        uint8_t OAMTABLE2BYTE06;
        uint8_t OAMTABLE2BYTE07;
        uint8_t OAMTABLE2BYTE08;
        uint8_t OAMTABLE2BYTE09;
        uint8_t OAMTABLE2BYTE10;
        uint8_t OAMTABLE2BYTE11;
        uint8_t OAMTABLE2BYTE12;
        uint8_t OAMTABLE2BYTE13;
        uint8_t OAMTABLE2BYTE14;
        uint8_t OAMTABLE2BYTE15;
        uint8_t OAMTABLE2BYTE16;
        uint8_t OAMTABLE2BYTE17;
        uint8_t OAMTABLE2BYTE18;
        uint8_t OAMTABLE2BYTE19;
        uint8_t OAMTABLE2BYTE20;
        uint8_t OAMTABLE2BYTE21;
        uint8_t OAMTABLE2BYTE22;
        uint8_t OAMTABLE2BYTE23;
        uint8_t OAMTABLE2BYTE24;
        uint8_t OAMTABLE2BYTE25;
        uint8_t OAMTABLE2BYTE26;
        uint8_t OAMTABLE2BYTE27;
        uint8_t OAMTABLE2BYTE28;
        uint8_t OAMTABLE2BYTE29;
        uint8_t OAMTABLE2BYTE30;
        uint8_t OAMTABLE2BYTE31;
    } Names;
    struct tagstOAMArray {
        struct sOAMEntry {
            uint8_t OBJX;
            uint8_t OBJY;
            uint8_t CHARNUM;
            uint8_t PROPERTIES;
        } OAMArray[128];
        unsigned char OAMTable2[32];
    } arr;
};

// Cross-compiler interrupt handler declarations
// Users MUST define these functions in their code for interrupt handling
// If not defined, the linker will fail with undefined symbols
// All interrupts (both emulation and native mode) use the same functions
//void snesXC_cop(void);   // COP (Coprocessor) interrupt
//void snesXC_brk(void);   // BRK (Break) interrupt  
//void snesXC_abort(void); // ABORT interrupt
//void snesXC_nmi(void);   // NMI (Non-Maskable Interrupt)
//void snesXC_irq(void);   // IRQ (Interrupt Request)

#endif //__SNES_REGS_H

