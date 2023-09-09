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
__attribute__((leaf)) char get_prg_bank(void);

// Get the current CHR bank.
// returns: The current bank.
__attribute__((leaf)) char get_chr_bank(void);

// Set the current 8kb chr bank to the bank with this id.
// this will take effect immediately
// and automatically rewrite at the top of every frame
__attribute__((leaf)) void set_chr_bank(char bank_id);

// Set the current 8kb chr bank to the bank with this id.
// this will take effect at the next frame
// and automatically rewrite at the top of every frame
__attribute__((leaf)) void swap_chr_bank(char bank_id);

// Set the current 8kb chr bank to the bank with this id.
// this will take effect immediately, such as for mid screen changes
// but then will be overwritten by the set_chr_bank() value
// in the next frame.
__attribute__((leaf)) void split_chr_bank(char bank_id);

// if you need to swap CHR banks mid screen, perhaps you need more
// than 256 unique tiles, first write (one time only) the CHR bank
// for the top of the screen with set_chr_bank().
// Then, every frame, time a mid screen split (probably with
// a sprite zero hit) and then change the CHR bank with
// split_chr_bank().
//
// example ---- in game loop
// split(0); ---- wait for sprite zero hit, set X scroll to 0
// split_chr_bank_0(6) ---- change CHR bank to #6

#define MIRROR_LOWER_BANK 0
#define MIRROR_UPPER_BANK 1
#define MIRROR_VERTICAL 2
#define MIRROR_HORIZONTAL 3

// Set the current mirroring mode. Your options are MIRROR_LOWER_BANK,
// MIRROR_UPPER_BANK, MIRROR_HORIZONTAL, and MIRROR_VERTICAL.
// LOWER and UPPER are single screen modes.
__attribute__((leaf)) void set_mirroring(char mirroring);

#ifdef __cplusplus
}
#endif

#endif // _BANK_H_
