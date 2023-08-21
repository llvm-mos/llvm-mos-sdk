// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from KickC. Modified from original version.

// clang-format off

/*
 * MIT License
 *
 * Copyright (c) 2017 Jesper Gravgaard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _MEGA65_VICIV_H
#define _MEGA65_VICIV_H

#ifdef __cplusplus
extern "C" {
#endif


/// @file
/// MEGA65 Video Interface Chip (VIC IV)
///
/// https://mega65.org/
/// https://github.com/MEGA65/mega65-core/blob/master/src/vhdl/viciv.vhdl
struct MEGA65_VICIV {
  char SPRITE0_X;
  char SPRITE0_Y;
  char SPRITE1_X;
  char SPRITE1_Y;
  char SPRITE2_X;
  char SPRITE2_Y;
  char SPRITE3_X;
  char SPRITE3_Y;
  char SPRITE4_X;
  char SPRITE4_Y;
  char SPRITE5_X;
  char SPRITE5_Y;
  char SPRITE6_X;
  char SPRITE6_Y;
  char SPRITE7_X;
  char SPRITE7_Y;
  char SPRITES_XMSB;
  char CONTROL1;
  char RASTER;
  char LIGHTPEN_X;
  char LIGHTPEN_Y;
  char SPRITES_ENABLE;
  char CONTROL2;
  char SPRITES_EXPAND_Y;
  char MEMORY;
  char IRQ_STATUS;
  char IRQ_ENABLE;
  char SPRITES_PRIORITY;
  char SPRITES_MC;
  char SPRITES_EXPAND_X;
  char SPRITES_COLLISION;
  char SPRITES_BG_COLLISION;
  /// $D020 Border Color
  char BORDER_COLOR;
  /// $D021 Background Color 0
  char BG_COLOR;
  /// $D022 Background Color 1
  char BG_COLOR1;
  /// $D023 Background Color 2
  char BG_COLOR2;
  /// $D024 Background Color 3
  char BG_COLOR3;
  /// $D025 Sprite multicolor 0
  char SPRITES_MCOLOR1;
  /// $D026 Sprite multicolor 1
  char SPRITES_MCOLOR2;
  /// $D027 Color Sprite 0
  char SPRITE0_COLOR;
  /// $D028 Color Sprite 1
  char SPRITE1_COLOR;
  /// $D029 Color Sprite 2
  char SPRITE2_COLOR;
  /// $D02a Color Sprite 3
  char SPRITE3_COLOR;
  /// $D02b Color Sprite 4
  char SPRITE4_COLOR;
  /// $D02c Color Sprite 5
  char SPRITE5_COLOR;
  /// $D02d Color Sprite 6
  char SPRITE6_COLOR;
  /// $D02e Color Sprite 7
  char SPRITE7_COLOR;
  /// $D02f KEY register is used for choosing between the different I/O personalities.
  /// This disables/enables different registers in $D000-$DFFF
  /// $00: C64 personality
  /// $A5, $96: C65 personality
  /// $45, $54: MEGA65 ETHERNET  personality
  /// $47, $53: MEGA65  personality
  char KEY;
  /// $D030 VIC-III Control Register A (ROM banks)
  /// Bit        20-bit Address       16-bit Address  Read-Write
  /// 0 CRAM2K   $1F800 – $1FFFF,     $D800 – $DFFF   Y
  ///            $FF80000 – $FF807FF
  /// 3 ROM8     $38000 – $39FFF      $8000 – $9FFF   N
  /// 4 ROMA     $3A000 – $3BFFF      $A000 – $BFFF   N
  /// 5 ROMC     $2C000 – $2CFFF      $C000 – $CFFF   N
  /// 6 CROM9    $29000 – $29FFF      $D000 – $DFFF   N
  /// 7 ROME     $3E000 – $3FFFF      $E000 – $FFFF   N
  char CONTROLA;
  /// $D031 VIC-III Control Register B
  /// BIT
  /// 0    INT   Enable VIC-III interlaced mode
  /// 1    MONO  Enable VIC-III MONO video output (not implemented)
  /// 2    H1280 Enable 1280 horizontal pixels (not implemented)
  /// 3    V400  Enable 400 vertical pixels
  /// 4    BPM   Bit-Plane Mode
  /// 5    ATTR  Enable extended attributes and 8 bit colour entries
  /// 6    FAST  Enable C65 FAST mode (3 .5MHz)
  /// 7    H640  Enable C64 640 horizontal pixels / 80 column mode
  char CONTROLB;
  char UNUSED;
  /// $D033  Bitplane 0 Address
  /// 1-3    B0ADEVN    Bitplane 0 address, even lines
  /// 5-7    B0ADODD    Bitplane 0 address, odd lines
  char B0_ADDR;
  /// $D034  Bitplane 1 Address
  char B1_ADDR;
  /// $D035  Bitplane 2 Address
  char B2_ADDR;
  /// $D036  Bitplane 3 Address
  char B3_ADDR;
  /// $D037  Bitplane 4 Address
  char B4_ADDR;
  /// $D038  Bitplane 5 Address
  char B5_ADDR;
  /// $D039  Bitplane 6 Address
  char B6_ADDR;
  /// $D03A  Bitplane 7 Address
  char B7_ADDR;
  /// $D03B  Complement bitplane flags
  char BPCOMP;
  /// $D03C  Bitplane X
  char BPX;
  /// $D03D  Bitplane Y
  char BPY;
  /// $D03E  Bitplane X Offset
  char HPOS;
  /// $D03F  Bitplane Y Offset
  char VPOS;
  /// $D040  Display Address Translater (DAT) Bitplane 0 port
  char B0PIX;
  /// $D041  Display Address Translater (DAT) Bitplane 1 port
  char B1PIX;
  /// $D042  Display Address Translater (DAT) Bitplane 2 port
  char B2PIX;
  /// $D043  Display Address Translater (DAT) Bitplane 3 port
  char B3PIX;
  /// $D044  Display Address Translater (DAT) Bitplane 4 port
  char B4PIX;
  /// $D045  Display Address Translater (DAT) Bitplane 5 port
  char B5PIX;
  /// $D046  Display Address Translater (DAT) Bitplane 6 port
  char B6PIX;
  /// $D047  Display Address Translater (DAT) Bitplane 7 port
  char B7PIX;
  /// $D048 top border position (low byte)
  char TBDRPOS_LO;
  /// $D049 top border position (high nibble) and sprite bitplane-modify-mode enables
  /// 0-3 Top border position (high nibble)
  /// 4-7 Sprite bitplane-modify-mode enables for sprite 0-3
  char TBDRPOS_HI;
  /// $D04A bottom border position (low byte)
  char BBDRPOS_LO;
  /// $D04B bottom border position (high nibble) and sprite bitplane-modify-mode enables
  /// 0-3 Bottom border position (high nibble)
  /// 4-7 Sprite bitplane-modify-mode enables for sprite 4-7
  char BBDRPOS_HI;
  /// $D04C character generator horizontal position (low byte)
  char TEXTXPOS_LO;
  /// $D04D character generator horizontal position (high nibble) and sprite horizontal tile enables
  /// 0-3 Character generator horizontal position (high nibble)
  /// 4-7 Sprite horizontal tile enables for sprite 0-3
  char TEXTXPOS_HI;
  /// $D04E character generator vertical position (low byte)
  char TEXTYPOS_LO;
  /// $D04F character generator vertical position (high nibble) and sprite horizontal tile enables
  /// 0-3 Character generator vertical position (high nibble)
  /// 4-7 Sprite horizontal tile enables for sprite 4-7
  char TEXTYPOS_HI;
  /// $D050 Read horizontal raster scan position (lower byte)
  char XPOS_LO;
  /// $D050 Read horizontal raster scan position (high byte)
  /// 0-5 Upper 6 bits of horizontal raster scan position
  /// 6-7 Always zero
  char XPOS_HI;
  /// $D052 Read physical raster position (low byte)
  /// -- Allow setting of fine raster for IRQ (low bits)
  char FNRASTER_LO;
  /// $D053 Read physical raster position (high bits)
  /// -- Allow setting of fine raster for IRQ (high bits)
  /// 0-2 Read physical raster position (high bits)
  /// 7   FNRST Raster compare source (1=VIC-IV fine raster, 0=VIC-II raster)
  char FNRASTER_HI;
  /// $D054 VIC-IV Control register C
  /// 0 CHR16 enable 16-bit character numbers (two screen bytes per character)
  /// 1 FCLRLO enable full-colour mode for character numbers <=\$FF
  /// 2 FCLRHI enable full-colour mode for character numbers >\$FF
  /// 3 SMTH video output horizontal smoothing enable
  /// 4 VIC-IV:SPR640 Sprite H640 enable;
  /// 5 VIC-IV:PALEMU video output pal simulation
  /// 6 VIC-IV:VFAST C65GS FAST mode (48MHz)
  /// 7 VIC-IV:ALPHEN Alpha compositor enable
  char CONTROLC;
  /// $D055 SPRHGTEN sprite extended height enable (one bit per sprite)
  char SPRHGTEN;
  /// $D056  Sprite extended height size (sprite pixels high)
  char SPRHGHT;
  /// $D057 SPRX64EN Sprite extended width enables (8 bytes per sprite row 64 pixels wide for normal sprites or 16 pixels wide for 16-colour sprite mode)
  char SPRX64EN;
  /// $D058 CHARSTEP_LO characters per logical text row (LSB)
  char CHARSTEP_LO;
  /// $D059 CHARSTEP_HI characters per logical text row (MSB)
  char CHARSTEP_HI;
  /// $D05A CHRXSCL Horizontal hardware scale of text mode (pixel 120ths per pixel)
  char CHRXSCL;
  /// $D05B CHRYSCL Vertical scaling of text mode (number of physical rasters per char text row)
  char CHRYSCL;
  /// $D05C SIDBDRWD Width of single side border (LSB)
  char SIDBDRWD_LO;
  /// $D05D SIDBDRWD side border width (MSB)
  /// 0-5 side border width (upper bits)
  ///   6 RSTDELEN Enable raster delay (delays raster counter and interrupts by one line to match output pipeline latency)
  ///   7 HOTREG Enable VIC-II hot registers. When enabled, touching many VIC-II registers causes the VIC-IV to recalculate display parameters, such as border positions and sizes.
  char SIDBDRWD_HI;
  /// $D05E CHRCOUNT Number of characters to display per row
  char CHRCOUNT;
  /// $D05F SPRXSMSBS Sprite H640 X Super-MSBs
  char SPRXSMSBS;
  /// $D060 SCRNPTR screen RAM precise base address (bits 0 - 7)
  char SCRNPTR_LOLO;
  /// $D061 SCRNPTR screen RAM precise base address (bits 15 - 8)
  char SCRNPTR_LOHI;
  /// $D062 SCRNPTR screen RAM precise base address (bits 23 - 16)
  char SCRNPTR_HILO;
  /// $D063 SCRNPTR screen RAM precise base address (bits 31 - 24)
  char SCRNPTR_HIHI;
  /// $D064 COLPTR colour RAM base address (bits 0 - 7)
  char COLPTR_LO;
  /// $D065 COLPTR colour RAM base address (bits 15 - 8)
  char COLPTR_HI;
  /// $D066 DEBUG1 (DEBUG WILL BE REMOVED)
  /// 0-4 VIC-IV xcounter pipeline delay (DEBUG WILL BE REMOVED)
  ///   6 VIC-IV render activity display enable (DEBUG WILL BE REMOVED)
  ///   7 VIC-IV test pattern display enable (DEBUG WILL BE REMOVED)
  char DEBUG1;
  /// $D067 SBPDEBUG Sprite/bitplane first X (DEBUG WILL BE REMOVED)
  char SBPDEBUG;
  /// $D068 CHARPTR Character set precise base address (bits 0 - 7)
  char CHARPTR_LOLO;
  /// $D069 CHARPTR Character set precise base address (bits 15 - 8)
  char CHARPTR_LOHI;
  /// $D06A CHARPTR Character set precise base address (bits 23 - 16)
  char CHARPTR_HILO;
  /// $D06B SPR16EN sprite 16-colour mode enables
  char SPR16EN;
  /// $D06C SPRPTRADR sprite pointer address (bits 7 - 0)
  char SPRPTRADR_LOLO;
  /// $D06D SPRPTRADR sprite pointer address (bits 15 - 8)
  char SPRPTRADR_LOHI;
  /// $D06E.0-6 SPRPTRADR sprite pointer address (bits 22 - 16)
  /// 0-6 sprite pointer address (bits 22 - 16)
  ///   7 SPRPTR16 16-bit sprite pointer mode (allows sprites to be located on any 64 byte boundary in chip RAM)
  char SPRPTRADR_HILO;
  /// $D06F First VIC-II raster line
  /// 0-5 RASLINE0 first VIC-II raster line
  ///   6 VGAHDTV Select more VGA-compatible mode if set, instead of HDMI/HDTV VIC-II cycle-exact frame timing. May help to produce a functional display on older VGA monitors.
  ///   7 PALNTSC NTSC emulation mode (max raster 262)
  /// bit 7 6
  ///     0 0 => PAL, 720x576 @ 50Hz
  ///     0 1 => PAL, 720x576 50Hz, NTSC max raster
  ///     1 0 => NTSC, 720x480 @ 60Hz
  ///     1 1 => NTSC 720x480 60Hz
  ///     ? ? => Default to NTSC 800x600 60Hz (see https://github.com/MEGA65/mega65-core/blob/master/src/vhdl/viciv.vhdl)
  char RASLINE0;
  /// $D070 VIC-IV palette bank selection
  /// 1-0 ABTPALSEL VIC-IV bitmap/text palette bank (alternate palette)
  /// 3-2 SPRPALSEL sprite palette bank
  /// 5-4 BTPALSEL bitmap/text palette bank
  /// 7-6 MAPEDPAL palette bank mapped at \$D100-\$D3FF
  char PALSEL;
  /// $D071 BP16ENS VIC-IV 16-colour bitplane enable flags
  char BP16ENS;
  /// $D072 VSYNDEL VIC-IV VSYNC delay
  char VSYNDEL;
  /// $D073 ALPHADELAY Alpha delay and raster height
  /// $D073.0-3 ALPHADELAY Alpha delay for compositor
  /// $D073.4-7 RASTERHEIGHT physical rasters per VIC-II raster (1 to 16)
  char ALPHADELAY;
  /// $D074 SPRENALPHA Sprite alpha-blend enable
  char SPRENALPHA;
  /// $D075 SPRALPHAVAL Sprite alpha-blend value
  char SPRALPHAVAL;
  /// $D076 SPRENV400 Sprite V400 enables
  char SPRENV400;
  /// $D077 SRPYMSBS Sprite V400 Y position MSBs
  char SRPYMSBS;
  /// $D078 SPRYSMSBS Sprite V400 Y position super MSBs
  char SPRYSMSBSM;
  /// $D079 RSTCOMP Raster compare value
  char RSTCOMP;
  /// $D07A RSTCMP Raster compare value MSB
  /// 0-2 RSTCMP Raster compare value MSB
  /// 3-6 RESERVED
  ///   7 FNRSTCMP Raster compare is in physical rasters if set, or VIC-II raster if clear
  char RSTCMP;
  /// $D07B Number of text rows to display
  char ROWCOUNT;
  /// $D07C hsync/vsync polarity
  /// 0-3 RESERVED UNUSED BITS
  ///   4 HSYNCP hsync polarity
  ///   5 VSYNCP vsync polarity
  /// 6-7 RESERVED UNUSED BITS
  char SYNCPOL;
  /// $D07D DEBUGX VIC-IV debug X position (LSB)
  char DEBUGX;
  /// $D07E DEBUGY VIC-IV debug Y position (LSB)
  char DEBUGY;
  /// $D07F DEBUGXY VIC-IV debug X/Y position (MSB)
  /// 0-5 DEBUGX VIC-IV debug X position (MSB)
  ///   7 DEBUGOOF VIC-IV debug out-of-frame signal enable
  /// 4-7 DEBUGY VIC-IV debug Y position (MSB)
  char DEBUGXY;
};

/// $D02f KEY register is used for choosing between the different I/O personalities.
/// This disables/enables different registers in $D000-$DFFF
/// $00: C64 personality
#define VICIV_KEY_C64 0x00
/// $A5, $96: C65 personality
#define VICIV_KEY_C65_A 0xa5
#define VICIV_KEY_C65_B 0x96
/// $45, $54: MEGA65 ETHERNET personality
#define VICIV_KEY_ETHERNET_A 0x45
#define VICIV_KEY_ETHERNET_B 0x54
/// $47, $53: MEGA65 personality
#define VICIV_KEY_M65_A 0x47
#define VICIV_KEY_M65_B 0x53

/// $D030 VIC-III Control Register A (ROM banks)
/// Bit        20-bit Address       16-bit Address  Read-Write
/// 0 CRAM2K   $1F800 – $1FFFF,     $D800 – $DFFF   Y
///            $FF80000 – $FF807FF
#define VICIV_CRAM2K 0x01
/// 3 ROM8     $38000 – $39FFF      $8000 – $9FFF   N
#define VICIV_ROM8 0x08
/// 4 ROMA     $3A000 – $3BFFF      $A000 – $BFFF   N
#define VICIV_ROMA 0x10
/// 5 ROMC     $2C000 – $2CFFF      $C000 – $CFFF   N
#define VICIV_ROMC 0x20
/// 6 CROM9    $29000 – $29FFF      $D000 – $DFFF   N
#define VICIV_CROM9 0x40
/// 7 ROME     $3E000 – $3FFFF      $E000 – $FFFF   N
#define VICIV_ROME 0x80

/// $D031 VIC-III Control Register B
/// 0    INT   Enable VIC-III interlaced mode
#define VICIV_INT 0x01
/// 1    MONO  Enable VIC-III MONO video output (not implemented)
#define VICIV_MONO 0x02
/// 2    H1280 Enable 1280 horizontal pixels (not implemented)
#define VICIV_H1280 0x04
/// 3    V400  Enable 400 vertical pixels
#define VICIV_V400 0x08
/// 4    BPM   Bit-Plane Mode
#define VICIV_BPM 0x10
/// 5    ATTR  Enable extended attributes and 8 bit colour entries
#define VICIV_ATTR 0x20
/// 6    FAST  Enable C65 FAST mode (3 .5MHz)
#define VICIV_FAST 0x40
/// 7    H640  Enable C64 640 horizontal pixels / 80 column mode
#define VICIV_H640 0x80

/// $D054 VIC-IV Control register C
/// 0 CHR16 enable 16-bit character numbers (two screen bytes per character)
#define VICIV_CHR16 0x01
/// 1 FCLRLO enable full-colour mode for character numbers <=\$FF
#define VICIV_FCLRLO 0x02
/// 2 FCLRHI enable full-colour mode for character numbers >\$FF
#define VICIV_FCLRHI 0x04
/// 3 SMTH video output horizontal smoothing enable
#define VICIV_CSMTH 0x08
/// 4 VIC-IV:SPR640 Sprite H640 enable;
#define VICIV_SPR640 0x10
/// 5 VIC-IV:PALEMU video output pal simulation
#define VICIV_PALEMU 0x20
/// 6 VIC-IV:VFAST C65GS FAST mode (48MHz)
#define VICIV_VFAST 0x40
/// 7 VIC-IV:ALPHEN Alpha compositor enable
#define VICIV_ALPHEN 0x80

/// $D06E.0-6 SPRPTRADR sprite pointer address (bits 22 - 16)
///   7 SPRPTR16 16-bit sprite pointer mode (allows sprites to be located on any 64 byte boundary in chip RAM)
#define VICIV_SPRPTR16 0x80

#ifdef __cplusplus
}
#endif
#endif 
