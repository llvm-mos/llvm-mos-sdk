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
#ifndef _MOS4569_H
#define _MOS4569_H

#ifdef __cplusplus
extern "C" {
#endif

/// @file
/// @brief MOS 4567 / 4569 Video Interface Chip (VIC III)

/// MOS 4567 / 4569 Video Interface Chip (VIC III)
struct MOS4569_VICIII {
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
};

#ifdef __cplusplus
}
#endif
#endif 
