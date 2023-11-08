// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MAPPER_BASE_H_
#define _MAPPER_BASE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char bank_index_t;

// Switch in a ROM bank.
__attribute__((weak, leaf)) void bank_select(bank_index_t bank_id);

// Switch in a ROM or RAM bank, depending on the high bit (if set, it's RAM)
__attribute__((weak, leaf)) void set_current_bank(bank_index_t bank_id);

// Get the currently switched bank index.
// If the high bit is set, it's a RAM bank, otherwise it's a ROM bank.
__attribute__((weak, leaf)) bank_index_t get_current_bank(void);

// Switch to another ROM bank and call this function.  Note: Using banked_call to
// call a second function from within another banked_call is safe. This function
// works no matter which switchable bank the function is in.
__attribute__((callback(2))) void banked_call_rom(bank_index_t bankId,
                                                        void (*method)(void));

#ifdef __cplusplus
}
#endif

#endif
