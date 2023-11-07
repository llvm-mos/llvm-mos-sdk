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

#ifndef _MAPPER_H_
#define _MAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

// Switch to another ROM bank and call this function.  Note: Using banked_call to
// call a second function from within another banked_call is safe. This function
// works no matter which switchable bank the function is in.
__attribute__((leaf, callback(2))) void banked_call_rom(char bankId,
                                                        void (*method)(void));

// Switch to another RAM bank and call this function.
__attribute__((leaf, callback(2))) void banked_call_ram(char bankId,
                                                        void (*method)(void));

// Switch in a ROM bank.
__attribute__((leaf)) void bank_select(char bank_id);

// Switch in a RAM bank.
__attribute__((leaf)) void ram_select(char bank_id);

// Switch in a ROM or RAM bank, depending on the high bit (if set, it's RAM)
__attribute__((leaf)) void set_current_bank(char bank_id);

// Get the currently switched bank index.
// If the high bit is set, it's a RAM bank, otherwise it's a ROM bank.
char get_current_bank(void);

// Write a byte to extended RAM at set address (0 - 0x3ff)
// RAM must be selected first, or use banked_call_ram
__attribute__((leaf)) void xram_write(int address, char value);

// Read a byte from extended RAM at set address (0 - 0x3ff)
// RAM must be selected first, or use banked_call_ram
__attribute__((leaf)) unsigned char xram_read(int address);


// From Stella (cartridge auto-detection):
// 3E cart RAM bankswitching is triggered by storing the bank number
// in address 3E using 'STA $3E', ROM bankswitching is triggered by
// storing the bank number in address 3F using 'STA $3F'.
// We expect the latter will be present at least 2 times, since there
// are at least two banks

#ifdef __cplusplus
}
#endif

#endif // _MAPPER_H_
