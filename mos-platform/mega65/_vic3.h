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
#ifndef _VIC3_H
#define _VIC3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/// @file
/// @brief MOS 4567 / 4569 Video Interface Chip (VIC III)

/// MOS 4567 / 4569 Video Interface Chip (VIC III)
struct __vic3 {
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
};

#ifdef __cplusplus
}
#endif
#endif // _VIC3_H
