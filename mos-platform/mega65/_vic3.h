// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _VIC3_H
#define _VIC3_H

/*
 * The following defines are auto-generated from iomap.txt.
 * See https://github.com/dansanderson/mega65-symbols
 * Date: 2023-08-25
 */

enum
#ifdef __clang__
    : uint8_t
#endif
{
  /** display border colour (256 colour) */
  VIC3_BORDERCOL_MASK = 0b11111111,
  /** screen colour (256 colour) */
  VIC3_SCREENCOL_MASK = 0b11111111,
  /** multi-colour 1 (256 colour) */
  VIC3_MC1_MASK = 0b11111111,
  /** multi-colour 2 (256 colour) */
  VIC3_MC2_MASK = 0b11111111,
  /** multi-colour 3 (256 colour) */
  VIC3_MC3_MASK = 0b11111111,
  /** Map 2nd KB of colour RAM @ $DC00-$DFFF */
  VIC3_CRAM2K_MASK = 0b00000001,
  /** Enable external video sync (genlock input) */
  VIC3_EXTSYNC_MASK = 0b00000010,
  /** Use PALETTE ROM (0) or RAM (1) entries for colours 0 - 15 */
  VIC3_PAL_MASK = 0b00000100,
  /** Map C65 ROM @ $8000 */
  VIC3_ROM8_MASK = 0b00001000,
  /** Map C65 ROM @ $A000 */
  VIC3_ROMA_MASK = 0b00010000,
  /** Map C65 ROM @ $C000 */
  VIC3_ROMC_MASK = 0b00100000,
  /** Select between C64 and C65 charset. */
  VIC3_CROM9_MASK = 0b01000000,
  /** Map C65 ROM @ $E000 */
  VIC3_ROME_MASK = 0b10000000,
  /** Enable VIC-III interlaced mode */
  VIC3_INT_MASK = 0b00000001,
  /** Enable VIC-III MONO video output (not implemented) */
  VIC3_MONO_MASK = 0b00000010,
  /** Enable 1280 horizontal pixels (not implemented) */
  VIC3_H1280_MASK = 0b00000100,
  /** Enable 400 vertical pixels */
  VIC3_V400_MASK = 0b00001000,
  /** Bit-Plane Mode */
  VIC3_BPM_MASK = 0b00010000,
  /** Enable extended attributes and 8 bit colour entries */
  VIC3_ATTR_MASK = 0b00100000,
  /** Enable C65 FAST mode (~3.5MHz) */
  VIC3_FAST_MASK = 0b01000000,
  /** Enable C64 640 horizontal pixels / 80 column mode */
  VIC3_H640_MASK = 0b10000000,
  /** Bitplane X address, even lines */
  VIC3_B0ADEVN_MASK = 0b00001110,
  /** Bitplane X address, odd lines */
  VIC3_B0ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B1ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B1ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B2ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B2ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B3ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B3ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B4ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B4ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B5ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B5ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B6ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B6ADODD_MASK = 0b11100000,
  /** @BXADEVN */
  VIC3_B7ADEVN_MASK = 0b00001110,
  /** @BXADODD */
  VIC3_B7ADODD_MASK = 0b11100000
};

#endif // _VIC3_H
