// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from KickC. Modified from original version.

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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _VIC4_H
#define _VIC4_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/// @file
/// MEGA65 Video Interface Chip (VIC IV)
///
/// https://mega65.org/
/// https://github.com/MEGA65/mega65-core/blob/master/src/vhdl/viciv.vhdl
struct __vic4 {
  /// $D020 Border Color
  uint8_t border_color;
  /// $D021 Background Color 0
  uint8_t bg_color;
  /// $D022 Background Color 1
  uint8_t bg_color1;
  /// $D023 Background Color 2
  uint8_t bg_color2;
  /// $D024 Background Color 3
  uint8_t bg_color3;
  /// $D025 Sprite multicolor 0
  uint8_t sprites_mcolor1;
  /// $D026 Sprite multicolor 1
  uint8_t sprites_mcolor2;
  /// $D027 Color Sprite 0
  uint8_t sprite0_color;
  /// $D028 Color Sprite 1
  uint8_t sprite1_color;
  /// $D029 Color Sprite 2
  uint8_t sprite2_color;
  /// $D02a Color Sprite 3
  uint8_t sprite3_color;
  /// $D02b Color Sprite 4
  uint8_t sprite4_color;
  /// $D02c Color Sprite 5
  uint8_t sprite5_color;
  /// $D02d Color Sprite 6
  uint8_t sprite6_color;
  /// $D02e Color Sprite 7
  uint8_t sprite7_color;
  /// $D02f KEY register is used for choosing between the different I/O
  /// personalities. This disables/enables different registers in $D000-$DFFF
  /// $00: C64 personality
  /// $A5, $96: C65 personality
  /// $45, $54: MEGA65 ETHERNET  personality
  /// $47, $53: MEGA65  personality
  uint8_t key;
  /// $D030 VIC-III Control Register A (ROM banks)
  /// Bit        20-bit Address       16-bit Address  Read-Write
  /// 0 CRAM2K   $1F800 – $1FFFF,     $D800 – $DFFF   Y
  ///            $FF80000 – $FF807FF
  /// 3 ROM8     $38000 – $39FFF      $8000 – $9FFF   N
  /// 4 ROMA     $3A000 – $3BFFF      $A000 – $BFFF   N
  /// 5 ROMC     $2C000 – $2CFFF      $C000 – $CFFF   N
  /// 6 CROM9    $29000 – $29FFF      $D000 – $DFFF   N
  /// 7 ROME     $3E000 – $3FFFF      $E000 – $FFFF   N
  uint8_t controla;
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
  uint8_t controlb;
  uint8_t unused;
  /// $D033  Bitplane 0 Address
  /// 1-3    B0ADEVN    Bitplane 0 address, even lines
  /// 5-7    B0ADODD    Bitplane 0 address, odd lines
  uint8_t b0_addr;
  /// $D034  Bitplane 1 Address
  uint8_t b1_addr;
  /// $D035  Bitplane 2 Address
  uint8_t b2_addr;
  /// $D036  Bitplane 3 Address
  uint8_t b3_addr;
  /// $D037  Bitplane 4 Address
  uint8_t b4_addr;
  /// $D038  Bitplane 5 Address
  uint8_t b5_addr;
  /// $D039  Bitplane 6 Address
  uint8_t b6_addr;
  /// $D03A  Bitplane 7 Address
  uint8_t b7_addr;
  /// $D03B  Complement bitplane flags
  uint8_t bpcomp;
  /// $D03C  Bitplane X
  uint8_t bpx;
  /// $D03D  Bitplane Y
  uint8_t bpy;
  /// $D03E  Bitplane X Offset
  uint8_t hpos;
  /// $D03F  Bitplane Y Offset
  uint8_t vpos;
  /// $D040  Display Address Translater (DAT) Bitplane 0 port
  uint8_t b0pix;
  /// $D041  Display Address Translater (DAT) Bitplane 1 port
  uint8_t b1pix;
  /// $D042  Display Address Translater (DAT) Bitplane 2 port
  uint8_t b2pix;
  /// $D043  Display Address Translater (DAT) Bitplane 3 port
  uint8_t b3pix;
  /// $D044  Display Address Translater (DAT) Bitplane 4 port
  uint8_t b4pix;
  /// $D045  Display Address Translater (DAT) Bitplane 5 port
  uint8_t b5pix;
  /// $D046  Display Address Translater (DAT) Bitplane 6 port
  uint8_t b6pix;
  /// $D047  Display Address Translater (DAT) Bitplane 7 port
  uint8_t b7pix;
  /// $D048 top border position (low byte)
  uint8_t tbdrpos_lo;
  /// $D049 top border position (high nibble) and sprite bitplane-modify-mode
  /// enables 0-3 Top border position (high nibble) 4-7 Sprite
  /// bitplane-modify-mode enables for sprite 0-3
  uint8_t tbdrpos_hi;
  /// $D04A bottom border position (low byte)
  uint8_t bbdrpos_lo;
  /// $D04B bottom border position (high nibble) and sprite bitplane-modify-mode
  /// enables 0-3 Bottom border position (high nibble) 4-7 Sprite
  /// bitplane-modify-mode enables for sprite 4-7
  uint8_t bbdrpos_hi;
  /// $D04C character generator horizontal position (low byte)
  uint8_t textxpos_lo;
  /// $D04D character generator horizontal position (high nibble) and sprite
  /// horizontal tile enables 0-3 Character generator horizontal position (high
  /// nibble) 4-7 Sprite horizontal tile enables for sprite 0-3
  uint8_t textxpos_hi;
  /// $D04E character generator vertical position (low byte)
  uint8_t textypos_lo;
  /// $D04F character generator vertical position (high nibble) and sprite
  /// horizontal tile enables 0-3 Character generator vertical position (high
  /// nibble) 4-7 Sprite horizontal tile enables for sprite 4-7
  uint8_t textypos_hi;
  /// $D050 Read horizontal raster scan position (lower byte)
  uint8_t xpos_lo;
  /// $D050 Read horizontal raster scan position (high byte)
  /// 0-5 Upper 6 bits of horizontal raster scan position
  /// 6-7 Always zero
  uint8_t xpos_hi;
  /// $D052 Read physical raster position (low byte)
  /// -- Allow setting of fine raster for IRQ (low bits)
  uint8_t fnraster_lo;
  /// $D053 Read physical raster position (high bits)
  /// -- Allow setting of fine raster for IRQ (high bits)
  /// 0-2 Read physical raster position (high bits)
  /// 7   FNRST Raster compare source (1=VIC-IV fine raster, 0=VIC-II raster)
  uint8_t fnraster_hi;
  /// $D054 VIC-IV Control register C
  /// 0 CHR16 enable 16-bit character numbers (two screen bytes per character)
  /// 1 FCLRLO enable full-colour mode for character numbers <=\$FF
  /// 2 FCLRHI enable full-colour mode for character numbers >\$FF
  /// 3 SMTH video output horizontal smoothing enable
  /// 4 VIC-IV:SPR640 Sprite H640 enable;
  /// 5 VIC-IV:PALEMU video output pal simulation
  /// 6 VIC-IV:VFAST C65GS FAST mode (48MHz)
  /// 7 VIC-IV:ALPHEN Alpha compositor enable
  uint8_t controlc;
  /// $D055 SPRHGTEN sprite extended height enable (one bit per sprite)
  uint8_t sprhgten;
  /// $D056  Sprite extended height size (sprite pixels high)
  uint8_t sprhght;
  /// $D057 SPRX64EN Sprite extended width enables (8 bytes per sprite row 64
  /// pixels wide for normal sprites or 16 pixels wide for 16-colour sprite
  /// mode)
  uint8_t sprx64en;
  /// $D058 CHARSTEP characters per logical text row
  uint16_t charstep;
  /// $D05A CHRXSCL Horizontal hardware scale of text mode (pixel 120ths per
  /// pixel)
  uint8_t chrxscl;
  /// $D05B CHRYSCL Vertical scaling of text mode (number of physical rasters
  /// per uint8_t text row)
  uint8_t chryscl;
  /// $D05C SIDBDRWD Width of single side border (LSB)
  uint8_t sidbdrwd_lo;
  /// $D05D SIDBDRWD side border width (MSB)
  /// 0-5 side border width (upper bits)
  ///   6 RSTDELEN Enable raster delay (delays raster counter and interrupts by
  ///   one line to match output pipeline latency) 7 HOTREG Enable VIC-II hot
  ///   registers. When enabled, touching many VIC-II registers causes the
  ///   VIC-IV to recalculate display parameters, such as border positions and
  ///   sizes.
  uint8_t sidbdrwd_hi;
  /// $D05E CHRCOUNT Number of characters to display per row
  uint8_t chrcount;
  /// $D05F SPRXSMSBS Sprite H640 X Super-MSBs
  uint8_t sprxsmsbs;
  /// $D060 SCRNPTR screen RAM precise base address (24 bit address)
  uint32_t scrnptr;
  /// $D064 COLPTR colour RAM base address
  uint16_t colptr;
  /// $D066 DEBUG1 (DEBUG WILL BE REMOVED)
  /// 0-4 VIC-IV xcounter pipeline delay (DEBUG WILL BE REMOVED)
  ///   6 VIC-IV render activity display enable (DEBUG WILL BE REMOVED)
  ///   7 VIC-IV test pattern display enable (DEBUG WILL BE REMOVED)
  uint8_t debug1;
  /// $D067 SBPDEBUG Sprite/bitplane first X (DEBUG WILL BE REMOVED)
  uint8_t sbpdebug;
  /// $D068 CHARPTR Character set precise base address (bits 0 - 7)
  uint8_t charptr_lolo;
  /// $D069 CHARPTR Character set precise base address (bits 15 - 8)
  uint8_t charptr_lohi;
  /// $D06A CHARPTR Character set precise base address (bits 23 - 16)
  uint8_t charptr_hilo;
  /// $D06B SPR16EN sprite 16-colour mode enables
  uint8_t spr16en;
  /// $D06C SPRPTRADR sprite pointer address (bits 7 - 0)
  uint8_t sprptradr_lolo;
  /// $D06D SPRPTRADR sprite pointer address (bits 15 - 8)
  uint8_t sprptradr_lohi;
  /// $D06E.0-6 SPRPTRADR sprite pointer address (bits 22 - 16)
  /// 0-6 sprite pointer address (bits 22 - 16)
  ///   7 SPRPTR16 16-bit sprite pointer mode (allows sprites to be located on
  ///   any 64 byte boundary in chip RAM)
  uint8_t sprptradr_hilo;
  /// $D06F First VIC-II raster line
  /// 0-5 RASLINE0 first VIC-II raster line
  ///   6 VGAHDTV Select more VGA-compatible mode if set, instead of HDMI/HDTV
  ///   VIC-II cycle-exact frame timing. May help to produce a functional
  ///   display on older VGA monitors. 7 PALNTSC NTSC emulation mode (max raster
  ///   262)
  /// bit 7 6
  ///     0 0 => PAL, 720x576 @ 50Hz
  ///     0 1 => PAL, 720x576 50Hz, NTSC max raster
  ///     1 0 => NTSC, 720x480 @ 60Hz
  ///     1 1 => NTSC 720x480 60Hz
  ///     ? ? => Default to NTSC 800x600 60Hz (see
  ///     https://github.com/MEGA65/mega65-core/blob/master/src/vhdl/viciv.vhdl)
  uint8_t rasline0;
  /// $D070 VIC-IV palette bank selection
  /// 1-0 ABTPALSEL VIC-IV bitmap/text palette bank (alternate palette)
  /// 3-2 SPRPALSEL sprite palette bank
  /// 5-4 BTPALSEL bitmap/text palette bank
  /// 7-6 MAPEDPAL palette bank mapped at \$D100-\$D3FF
  uint8_t palsel;
  /// $D071 bp16ens VIC-IV 16-colour bitplane enable flags
  uint8_t bp16ens;
  /// $D072 VSYNDEL VIC-IV VSYNC delay
  uint8_t vsyndel;
  /// $D073 ALPHADELAY Alpha delay and raster height
  /// $D073.0-3 ALPHADELAY Alpha delay for compositor
  /// $D073.4-7 RASTERHEIGHT physical rasters per VIC-II raster (1 to 16)
  uint8_t alphadelay;
  /// $D074 SPRENALPHA Sprite alpha-blend enable
  uint8_t sprenalpha;
  /// $D075 SPRALPHAVAL Sprite alpha-blend value
  uint8_t spralphaval;
  /// $D076 SPRENV400 Sprite V400 enables
  uint8_t sprenv400;
  /// $D077 SRPYMSBS Sprite V400 Y position MSBs
  uint8_t srpymsbs;
  /// $D078 SPRYSMSBS Sprite V400 Y position super MSBs
  uint8_t sprysmsbsm;
  /// $D079 RSTCOMP Raster compare value
  uint8_t rstcomp;
  /// $D07A RSTCMP Raster compare value MSB
  /// 0-2 RSTCMP Raster compare value MSB
  /// 3-6 RESERVED
  ///   7 FNRSTCMP Raster compare is in physical rasters if set, or VIC-II
  ///   raster if clear
  uint8_t rstcmp;
  /// $D07B Number of text rows to display
  uint8_t rowcount;
  /// $D07C hsync/vsync polarity
  /// 0-3 RESERVED UNUSED BITS
  ///   4 HSYNCP hsync polarity
  ///   5 VSYNCP vsync polarity
  /// 6-7 RESERVED UNUSED BITS
  uint8_t syncpol;
  /// $D07D DEBUGX VIC-IV debug X position (LSB)
  uint8_t debugx;
  /// $D07E DEBUGY VIC-IV debug Y position (LSB)
  uint8_t debugy;
  /// $D07F DEBUGXY VIC-IV debug X/Y position (MSB)
  /// 0-5 DEBUGX VIC-IV debug X position (MSB)
  ///   7 DEBUGOOF VIC-IV debug out-of-frame signal enable
  /// 4-7 DEBUGY VIC-IV debug Y position (MSB)
  uint8_t debugxy;
};

/// $D02f KEY register is used for choosing between the different I/O
/// personalities. This disables/enables different registers in $D000-$DFFF $00:
/// C64 personality
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
///   7 SPRPTR16 16-bit sprite pointer mode (allows sprites to be located on any
///   64 byte boundary in chip RAM)
#define VICIV_SPRPTR16 0x80

#ifdef __cplusplus
}
#endif
#endif // _VIC4_H
