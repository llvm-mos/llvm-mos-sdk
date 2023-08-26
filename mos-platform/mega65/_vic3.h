// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _VIC3_H
#define _VIC3_H

/*
 * The following defines are auto-generated from iomap.txt.
 * See https://github.com/mega65/mega65-symbols
 */

/** display border colour (256 colour) */
#define VIC3_BORDERCOL_MASK 0b11111111

/** screen colour (256 colour) */
#define VIC3_SCREENCOL_MASK 0b11111111

/** multi-colour 1 (256 colour) */
#define VIC3_MC1_MASK 0b11111111

/** multi-colour 2 (256 colour) */
#define VIC3_MC2_MASK 0b11111111

/** multi-colour 3 (256 colour) */
#define VIC3_MC3_MASK 0b11111111

/** Map 2nd KB of colour RAM @ $DC00-$DFFF */
#define VIC3_CRAM2K_MASK 0b00000001

/** Enable external video sync (genlock input) */
#define VIC3_EXTSYNC_MASK 0b00000010

/** Use PALETTE ROM (0) or RAM (1) entries for colours 0 - 15 */
#define VIC3_PAL_MASK 0b00000100

/** Map C65 ROM @ $8000 */
#define VIC3_ROM8_MASK 0b00001000

/** Map C65 ROM @ $A000 */
#define VIC3_ROMA_MASK 0b00010000

/** Map C65 ROM @ $C000 */
#define VIC3_ROMC_MASK 0b00100000

/** Select between C64 and C65 charset. */
#define VIC3_CROM9_MASK 0b01000000

/** Map C65 ROM @ $E000 */
#define VIC3_ROME_MASK 0b10000000

/** Enable VIC-III interlaced mode */
#define VIC3_INT_MASK 0b00000001

/** Enable VIC-III MONO video output (not implemented) */
#define VIC3_MONO_MASK 0b00000010

/** Enable 1280 horizontal pixels (not implemented) */
#define VIC3_H1280_MASK 0b00000100

/** Enable 400 vertical pixels */
#define VIC3_V400_MASK 0b00001000

/** Bit-Plane Mode */
#define VIC3_BPM_MASK 0b00010000

/** Enable extended attributes and 8 bit colour entries */
#define VIC3_ATTR_MASK 0b00100000

/** Enable C65 FAST mode (~3.5MHz) */
#define VIC3_FAST_MASK 0b01000000

/** Enable C64 640 horizontal pixels / 80 column mode */
#define VIC3_H640_MASK 0b10000000

/** Bitplane X address, even lines */
#define VIC3_B0ADEVN_MASK 0b00001110

/** Bitplane X address, odd lines */
#define VIC3_B0ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B1ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B1ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B2ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B2ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B3ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B3ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B4ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B4ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B5ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B5ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B6ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B6ADODD_MASK 0b11100000

/** @BXADEVN */
#define VIC3_B7ADEVN_MASK 0b00001110

/** @BXADODD */
#define VIC3_B7ADODD_MASK 0b11100000

#endif // _VIC3_H

