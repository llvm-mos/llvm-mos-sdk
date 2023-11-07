// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MAPPER_H_
#define _MAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char bank_index_t;

// Switch to another ROM bank and call this function.  Note: Using banked_call to
// call a second function from within another banked_call is safe. This function
// works no matter which switchable bank the function is in.
__attribute__((callback(2))) void banked_call_rom(bank_index_t bankId,
                                                        void (*method)(void));

// Switch in a ROM bank.
__attribute__((weak, leaf)) void bank_select(bank_index_t bank_id);

// Switch in a ROM or RAM bank, depending on the high bit (if set, it's RAM)
__attribute__((weak, leaf)) void set_current_bank(bank_index_t bank_id);

// Get the currently switched bank index.
// If the high bit is set, it's a RAM bank, otherwise it's a ROM bank.
__attribute__((weak, leaf)) bank_index_t get_current_bank(void);

// Switch in a RAM bank.
__attribute__((weak, leaf)) void ram_select(bank_index_t bank_id);

// Switch to another RAM bank and call this function.
__attribute__((callback(2))) void banked_call_ram(bank_index_t bankId,
                                                        void (*method)(void));

// Write a byte to extended RAM at set address (0 - 0x3ff)
// RAM must be selected first, or use banked_call_ram
__attribute__((leaf)) void xram_write(int address, unsigned char value);

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
