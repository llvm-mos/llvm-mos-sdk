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

#ifdef __cplusplus
extern "C" {
#endif

// Contains functions to help with working with multiple PRG/CHR banks
// For MMC3 code.

// Switch to another bank and call this function.  Note: Using banked_call to
// call a second function from within another banked_call is safe. This function
// works no matter which switchable bank the function is in.
__attribute__((leaf, callback(2))) void banked_call(char bankId,
                                                    void (*method)(void));

// Same as banked_call, but assumes the bank is 8000/c000.
__attribute__((leaf, callback(2))) void banked_call_8000(char bankId,
                                                         void (*method)(void));

// Same as banked_call, but assumes the bank is a000.
__attribute__((leaf, callback(2))) void banked_call_a000(char bankId,
                                                         void (*method)(void));

// Sets the bank at the address with the given high byte.
__attribute__((leaf)) void set_prg_bank(char bank_id, char addr_hi);

// Gets the bank at the address with the given high byte.
__attribute__((leaf)) char get_prg_bank(char addr_hi);

// Switch to the given bank (at $8000-9fff or $c000-dfff). Your prior bank is
// not saved.
// bank_id: The bank to switch to.
__attribute__((leaf)) void set_prg_8000(char bank_id);

// Get the current PRG bank at $8000-9fff (or $c000-dfff).
// returns: The current bank.
char get_prg_8000(void);

// Switch to the given bank (at $a000-bfff). Your prior bank is not saved.
// bank_id: The bank to switch to.
__attribute__((leaf)) void set_prg_a000(char bank_id);

// Get the current PRG bank at $a000-bfff.
// returns: The current bank.
char get_prg_a000(void);

// Changes a portion of the tilesets. If interrupted, these may have no effect.
// All but the low three bits of reg must be zero.
__attribute__((leaf)) void set_chr_bank(char reg, char bank_id);

// Same as set_chr_bank, but retries if interrupted.
__attribute__((leaf)) void set_chr_bank_retry(char bank, char bank_id);

// Same as the above, but hard-code the bank.
void set_chr_mode_0(char chr_id);
void set_chr_mode_1(char chr_id);
void set_chr_mode_2(char chr_id);
void set_chr_mode_3(char chr_id);
void set_chr_mode_4(char chr_id);
void set_chr_mode_5(char chr_id);

#define MIRROR_VERTICAL 0
#define MIRROR_HORIZONTAL 1

// Set the current mirroring mode. Your options are
// MIRROR_HORIZONTAL, and MIRROR_VERTICAL.
__attribute__((leaf)) void set_mirroring(char mirroring);

#define PRG_MODE_0 0
#define PRG_MODE_1 0x40
// Set the PRG ROM bank mode. Takes effect after the next PRG or CHR bank
// switch.
void set_prg_mode(char mode);

#define CHR_A12_STRAIGHT 0
#define CHR_A12_INVERT   0x80
// Set whether CHR A12 is inverted. Takes effect after the next PRG or CHR bank
// switch.
void set_chr_a12_inversion(char mode);

#define WRAM_OFF 0x40
#define WRAM_ON 0x80
#define WRAM_READ_ONLY 0xC0

// Set the WRAM mode. Your options are
// WRAM_OFF, WRAM_ON, and WRAM_READ_ONLY.
// May not work in some emulators.
__attribute__((leaf)) void set_wram_mode(char mode);

// Turns off MMC3 irqs, and changes the array pointer
// to point to a default 0xff
__attribute__((leaf)) void disable_irq(void);

// This points an array to the IRQ system
// Also turns ON the system
__attribute__((leaf)) void set_irq_ptr(const void *address);

// Check if it's safe to write to the irq array
// returns 0xff if done, zero if not done
// if the irq pointer is pointing to 0xff it is
// safe to edit.
__attribute__((leaf)) char is_irq_done(void);

#ifdef __cplusplus
}
#endif

#endif // _BANK_H_
