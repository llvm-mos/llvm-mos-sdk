// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.
//
// Copyright 2019 Doug Fraker
// Copyright 2018 Christopher Parker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _BANK_H_
#define _BANK_H_

#include <ines.h>

#ifdef __cplusplus
extern "C" {
#endif

// Contains functions to help with working with multiple PRG/CHR banks

// Maximum level of recursion to allow with banked_call and similar functions.
#define MAX_BANK_DEPTH 10

// Switch to another bank and call this function.
// Note: Using banked_call to call a second function from within
// another banked_call is safe.
__attribute__((leaf, callback(2))) void banked_call(char bank_id,
                                                    void (*method)(void));

// Switch to the given bank (to $8000-bfff). Your prior bank is not saved.
// Can be used for reading data with a function in the fixed bank.
// bank_id: The bank to switch to.
__attribute__((leaf)) void set_prg_bank(char bank_id);

// Get the current PRG bank at $8000-bfff.
// returns: The current bank.
char get_prg_bank(void);

// NOTE: On some MMC1 boards, the high bits of the CHR bank control PRG-ROM/RAM
// state. For the functions immediately below, these high bits must be zero; use
// the high versions of the getters and setters below to reference these bits.

// Set the current 1st 4k chr bank to the bank with this id.
// This will take effect immediately and automatically rewrite at the top of
// every frame. May have no immediate effect if interrupted by NMI.
void set_chr_bank_0(char bank_id);

// Set the current 2nd 4k chr bank to the bank with this id.
// This will take effect immediately and automatically rewrite at the top of
// every frame. May have no immediate effect if interrupted by NMI.
void set_chr_bank_1(char bank_id);

// Set the current 1st 4k chr bank to the bank with this id.
// this will take effect immediately, such as for mid screen changes
// but then will be overwritten by the `[set/defer]_chr_bank_0()` value
// in the next frame. May have no effect if interrupted by NMI.
void split_chr_bank_0(char bank_id);

// Set the current 2nd 4k chr bank to the bank with this id.
// this will take effect immediately, such as for mid screen changes
// but then will be overwritten by the `[set/defer]_chr_bank_1()` value
// in the next frame. May have no effect if interrupted by NMI.
void split_chr_bank_1(char bank_id);

// Set the current 1st 4k chr bank to the bank with this id.
// This will take effect at the next frame and automatically rewrite at the top
// of every frame.
void defer_chr_bank_0(char bank_id);

// Set the current 2nd 4k chr bank to the bank with this id.
// This will take effect at the next frame and automatically rewrite at the top
// of every frame.
void defer_chr_bank_1(char bank_id);

// Return the high bits of CHR bank 0 that control PRG-RAM/ROM state. The return
// value is not shifted.
char get_chr_bank_0_high(void);

// Sets the high bits of the CHR bank 0 register that control PRG-RAM/ROM state
// to the given value. The incoming value is not shifted, and the lower bits
// that control the CHR bank must be zero.
void set_chr_bank_0_high(char value);

// Return the high bits of CHR bank 1 that control PRG-RAM/ROM state. The return
// value is not shifted.
char get_chr_bank_1_high(void);

// Sets the high bits of the CHR bank 1 register that control PRG-RAM/ROM state
// to the given value. The incoming value is not shifted, and the lower bits
// that control the CHR bank must be zero.
void set_chr_bank_1_high(char value);

// if you need to swap CHR banks mid screen, perhaps you need more
// than 256 unique tiles, first write (one time only) the CHR bank
// for the top of the screen with set_chr_bank_0().
// Then, every frame, time a mid screen split (probably with
// a sprite zero hit) and then change the CHR bank with
// split_chr_bank_0().
//
// example ---- in game loop
// split(0); ---- wait for sprite zero hit, set X scroll to 0
// split_chr_bank_0(6) ---- change CHR bank to #6

enum Mirroring {
  MIRROR_LOWER_BANK = 0,
  MIRROR_UPPER_BANK,
  MIRROR_VERTICAL,
  MIRROR_HORIZONTAL,
};

// Set the current mirroring mode. Your options are MIRROR_LOWER_BANK,
// MIRROR_UPPER_BANK, MIRROR_HORIZONTAL, and MIRROR_VERTICAL.
// LOWER and UPPER are single screen modes. Applies immediately and reapplies at
// each NMI. May have no immediate effect if interrupted by NMI.
void set_mirroring(enum Mirroring mirroring);

// Set the mirroring temporarily, but override with the previous setting at next
// NMI. May have no effect if interrupted by NMI.
void split_mirroring(enum Mirroring mirroring);

// Set the mirroring to be applied automatically at the next NMI.
void defer_mirroring(enum Mirroring mirroring);

enum ChrBankMode {
  CHR_BANK_MODE_8 = 0b00000,
  CHR_BANK_MODE_4 = 0b10000,
};

// Set the current CHR bank mode. Applies immediately and reapplies at
// each NMI. May have no immediate effect if interrupted by NMI.
void set_chr_bank_mode(enum ChrBankMode mode);

// Set the CHR bank mode temporarily, but override with the previous setting
// at next NMI. May have no effect if interrupted by NMI.
void split_chr_bank_mode(enum ChrBankMode mode);

// Set the CHR bank mode to be applied automatically at the next NMI.
void defer_chr_bank_mode(enum ChrBankMode mode);

enum PrgRomBankMode {
  PRG_ROM_BANK_MODE_32K = 0b00000,
  PRG_ROM_BANK_MODE_FIXED_8000 = 0b01000,
  PRG_ROM_BANK_MODE_FIXED_C000 = 0b01100,
};
// Change the PRG-ROM bank mode.
void set_prg_rom_bank_mode(enum PrgRomBankMode mode);

// Return the current PRG-ROM bank mode.
enum PrgRomBankMode get_prg_rom_bank_mode(void);

// Set all 5 bits of the $8000 MMC1 Control register. The mirroring and CHR-ROM
// bank mode settings are applied immediately and at future NMIs.
void set_mmc1_ctrl(char value);

// The mirroring and CHR-ROM bank mode settings are applied immediately, but
// will be overwritten by future NMIs. The PRG-ROM bits are ignored. May have no
// effect if interruped by NMI.
void split_mmc1_ctrl(char value);

// The mirroring and CHR-ROM bank mode settings are applied immediately, but
// will be overwritten by future NMIs. The PRG-ROM bits are ignored.
void defer_mmc1_ctrl(char value);

#ifdef __cplusplus
}
#endif

#endif // _BANK_H_
