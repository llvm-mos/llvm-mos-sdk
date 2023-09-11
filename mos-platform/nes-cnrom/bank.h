// Copyright 2022, 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _BANK_H_
#define _BANK_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the current CHR bank.
 * 
 * @return The current CHR bank.
 */
__attribute__((leaf)) char get_chr_bank(void);

/**
 * @brief Switch to the given CHR bank.
 * 
 * @param bank_id The bank ID to switch to.
 */
__attribute__((leaf)) void set_chr_bank(char bank_id);

#ifdef __cplusplus
}
#endif

#endif // _BANK_H_
