// Copyright 2022, 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _BANK_H_
#define _BANK_H_

#include <ines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Call a function from the given $8000-$BFFF PRG bank.
 * 
 * @param bank_id The bank ID to use.
 * @param method The method to call.
 */
__attribute__((leaf, callback(2))) void banked_call(char bank_id,
                                                    void (*method)(void));

/**
 * @brief Get the current $8000-$BFFF PRG bank.
 * 
 * @return The current PRG bank.
 */
__attribute__((leaf)) char get_prg_bank(void);

/**
 * @brief Switch to the given $8000-$BFFF PRG bank.
 * 
 * @param bank_id The bank ID to switch to.
 */
__attribute__((leaf)) void set_prg_bank(char bank_id);

#ifdef __cplusplus
}
#endif

#endif // _BANK_H_
