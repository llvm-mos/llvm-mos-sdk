// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Mapper functions for single-area bank switching schemes.
// (F8, F6, F4, 3E, FA, E7, F0, UA, 0840)

#ifndef _MAPPER_ROM_SINGLE_H_
#define _MAPPER_ROM_SINGLE_H_

#ifdef __cplusplus
extern "C" {
#endif

// ROM bank index type.
typedef unsigned char rom_bank_t;

// Switch in a ROM bank.
void bank_select(rom_bank_t bank_id);

// Switch in a ROM or RAM bank, depending on the high bit (if set, it's RAM)
void set_current_bank(rom_bank_t bank_id);

// Get the currently switched bank index.
// If the high bit is set, it's a RAM bank, otherwise it's a ROM bank.
rom_bank_t get_current_bank(void);

// Switch to another ROM bank and call this function.  Note: Using banked_call to
// call a second function from within another banked_call is safe. This function
// works no matter which switchable bank the function is in.
__attribute__((callback(2))) void banked_call_rom(rom_bank_t bank_id,
                                                  void (*method)(void));

#ifdef __cplusplus
}
#endif

#endif
