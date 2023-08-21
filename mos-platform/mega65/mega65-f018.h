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
#ifndef _MEGA65_F018_H
#define _MEGA65_F018_H

#ifdef __cplusplus
extern "C" {
#endif


/// @file
/// MEGA65 DMA
///
/// Appendix J in https://mega.scryptos.com/sharefolder-link/MEGA/MEGA65+filehost/Docs/MEGA65-Book_draft.pdf
/// C65 Manual http://www.zimmers.net/cbmpics/cbm/c65/c65manual.txt
/// DMA lists https://raw.githubusercontent.com/MEGA65/c65-specifications/master/c65manualupdated.txt
/// DMA lists https://c65gs.blogspot.com/2019/03/auto-detecting-required-revision-of.html
/// DMA list options https://c65gs.blogspot.com/2018/01/improving-dmagic-controller-interface.html
/// DMAgic VHDL source https://github.com/MEGA65/mega65-core/blob/master/src/vhdl/gs4510.vhdl#L4364
/// Xemu emulator source https://github.com/lgblgblgb/xemu/blob/master/xemu/f018_core.c

/// Registers of the MEGA65 enchanced F018 DMAgic Controller
struct F018_DMAGIC {
    /// $D700 ADDRLSBTRIG DMAgic DMA list address LSB, and trigger DMA (when written).
    /// We also clear out the upper address bits in case an enhanced job had set them.
    char ADDRLSBTRIG;
    /// $D701 ADDRMSB DMA list address high byte (address bits 8 -- 15).
    char ADDRMSB;
    /// $D702 ADDRBANK DMA list address bank (address bits 16 -- 22). Writing clears $D704.
    char ADDRBANK;
    /// $D703 EN018B DMA enable F018B mode (adds sub-command byte )
    /// bit 0 enable F018B mode.
    char EN018B;
    /// $D704 ADDRMB DMA list address mega-byte
    char ADDRMB;
    /// $D705 ETRIG Set low-order byte of DMA list address, and trigger Enhanced DMA job
    /// Works like $D700, but enables DMA option lists.
    char ETRIG;
    /// $D706-$D70D Unused
    char UNUSED1[8];
    /// $D70E ADDRLSB DMA list address low byte (address bits 0 -- 7) WITHOUT STARTING A DMA JOB
    /// (used by Hypervisor for unfreezing DMA-using tasks)
    char ADDRLSB;
    /// $D70F Unused
    char UNUSED2;
    /// $D710 MISC (non-DMA) options
    /// $D710.0 - MISC:BADLEN Enable badline emulation
    /// $D710.1 - MISC:SLIEN Enable 6502-style slow (7 cycle) interrupts
    /// $D710.2 - MISC:VDCSEN Enable VDC interface simulation
    char MISC;
};

/// F018A DMA list entry
struct DMA_LIST_F018A {
        /// DMA command
        /// 0-1 command (00: copy, 01: mix (unsupported) 10: swap (unsupported) 11: fill )
        ///   2 chain
        ///   3 allow interrupt (unsupported)
        char command;
        /// Count of bytes to copy/fill
        unsigned int count;
        /// Source address (low byte is used as data for command fill)
        char* src;
        /// Source address bank
        /// bits
        ///    7 src I/O
        ///    6 src direction
        ///    5 src modulo
        ///    4 src hold
        ///  0-3 address bank (which 64k bank is the address in)
        char src_bank;
        /// Destination address
        char* dest;
        /// Destination address bank
        /// bits
        ///    7 dest I/O
        ///    6 dest direction
        ///    5 dest modulo
        ///    4 dest hold
        ///  0-3 address bank (which 64k bank is the address in)
        char dest_bank;
        /// Modulo value (unused)
        unsigned int modulo;
};

/// F018B DMA list entry
struct DMA_LIST_F018B {
        /// DMA command (format F018B)
        /// bits
        /// 0-1 command (00: copy, 01: mix (unsupported) 10: swap (unsupported) 11: fill )
        ///   2 chain
        ///   3 allow interrupt (unsupported)
        ///   4 src direction
        ///   5 dest direction
        char command;
        /// Count of bytes to copy/fill
        unsigned int count;
        /// Source address (low byte is used as data for command fill)
        char* src;
        /// Source address bank
        /// bits
        ///    7 src I/O
        ///  0-6 dest address bank (which 64k bank is the address in)
        char src_bank;
        /// Destination address
        char* dest;
        /// Destination address bank
        /// bits
        ///    7 dest I/O
        ///  0-6 dest address bank (which 64k bank is the address in)
        char dest_bank;
        /// Sub-command
        /// bits
        ///   0 src modulo (unsupported)
        ///   1 src hold
        ///   2 dest modulo (unsupported)
        ///   3 dest hold
        char sub_command;
        /// Modulo value (unused)
        unsigned int modulo;
};

/// DMA command copy
#define DMA_COMMAND_COPY 0x00
/// DMA command fill
#define DMA_COMMAND_FILL 0x03
/// DMA command fill
#define DMA_COMMAND_CHAIN 0x04
/// DMA command source direction
#define DMA_COMMAND_SRC_DIR 0x10
/// DMA command destination direction
#define DMA_COMMAND_DEST_DIR 0x20

/// Extended DMA Option Prefixes

/// $00 End of options
#define DMA_OPTION_END 0x00
/// $06 Use $86 $xx transparency value (don't write source bytes to destination, if byte value matches $xx)
#define DMA_OPTION_TRANSPARENCY_ENABLE 0x06
/// $07 Disable $86 $xx transparency value.
#define DMA_OPTION_TRANSPARENCY_DISABLE 0x07
/// $0A Use F018A list format
#define DMA_OPTION_FORMAT_F018A 0x0a
/// $0B Use F018B list format
#define DMA_OPTION_FORMAT_F018B 0x0a
/// $53 Enable ‘Shallan Spiral’ Mode
#define DMA_OPTION_SPIRAL 0x53
/// $80 $xx Set MB of source address
#define DMA_OPTION_SRC_MB 0x80
/// $81 $xx Set MB of destination address
#define DMA_OPTION_DEST_MB 0x81
/// $82 $xx Set source skip rate (/256ths of bytes)
#define DMA_OPTION_SRC_SKIPRATE_256TH 0x82
/// $83 $xx Set source skip rate (whole bytes)
#define DMA_OPTION_SRC_SKIPRATE 0x83
/// $84 $xx Set destination skip rate (/256ths of bytes)
#define DMA_OPTION_DEST_SKIPRATE_256TH 0x84
/// $85 $xx Set destination skip rate (whole bytes)
#define DMA_OPTION_DEST_SKIPRATE 0x85
/// $86 $xx Don't write to destination if byte value $xx, and option $06 enabled
#define DMA_OPTION_TRANSPARENCY_VALUE 0x86
/// $87 Set X column bytes (LSB) for line drawing
/// The number of bytes needed to move to the next X column (8 pixels to the right)
#define DMA_OPTION_LINE_XSTEP_LO 0x87
/// $88 Set X column bytes (MSB) for line drawing
/// The number of bytes needed to move to the next X column (8 pixels to the right)
#define DMA_OPTION_LINE_XSTEP_HI 0x88
/// $89 Set Y row bytes (LSB) for line drawing
/// The number of bytes needed to move to the next Y row (1 pixel below)
#define DMA_OPTION_LINE_YSTEP_LO 0x89
/// $8A Set Y row bytes (MSB) for line drawing
/// The number of bytes needed to move to the next Y row (1 pixel below)
#define DMA_OPTION_LINE_YSTEP_HI 0x8a
/// $8B Slope (LSB) for line drawing
#define DMA_OPTION_LINE_SLOPE_LO 0x8b
/// $8C Slope (MSB) for line drawing
#define DMA_OPTION_LINE_SLOPE_HI 0x8c
/// $8D Slope accumulator initial fraction (LSB) for line drawing
#define DMA_OPTION_LINE_SLOPE_INIT_LO 0x8d
/// $8E Slope accumulator initial fraction (MSB) for line drawing
#define DMA_OPTION_LINE_SLOPE_INIT_HI 0x8e
/// $8F Line Drawing Mode enable and options (set in argument byte):
/// Bit 7 enable line mode,
/// Bit 6 select X or Y direction,
/// Bit 5 slope is negative.
#define DMA_OPTION_LINE_MODE 0x8f
/// Line Drawing Mode Bit 7 enable line mode,
#define DMA_OPTION_LINE_MODE_ENABLE 0x80
/// Line Drawing Mode Bit 6 select X or Y direction,
#define DMA_OPTION_LINE_MODE_DIRECTION_Y 0x40
/// Line Drawing Mode Bit 5 slope is negative.
#define DMA_OPTION_LINE_MODE_SLOPE_NEGATIVE 0x20

#ifdef __cplusplus
}
#endif
#endif 

