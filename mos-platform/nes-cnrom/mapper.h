// Copyright 2022, 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MAPPER_H_
#define _MAPPER_H_

#include <ines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Switch to the given CHR bank.
 * 
 * @param bank_id The bank ID to switch to.
 */
__attribute__((leaf)) void set_chr_bank(char bank_id);

/**
 * @brief Switch to the given CHR bank at the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to.
 */
__attribute__((leaf)) void swap_chr_bank(char bank_id);

/**
 * @brief Switch to the given CHR bank until the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to.
 */
__attribute__((leaf)) void split_chr_bank(char bank_id);

#ifdef __cplusplus
}
#endif

#endif // _MAPPER_H_
