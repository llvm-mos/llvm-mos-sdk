// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MAPPER_H_
#define _MAPPER_H_

#include <stdbool.h>
#include <ines.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PRG_BANK_MASK         0x0F
#define PRG_BANK_SHIFT        0
#define CHR_BANK_MASK  0x10
#define CHR_BANK_SHIFT 4
#define CHR_BANK_0	  0x00
#define CHR_BANK_1	  0x10
#define NT_BANK_MASK   0x20
#define NT_BANK_SHIFT  5
#define NT_BANK_0	  0x00
#define NT_BANK_1	  0x20
#define MAPPER_RED_LED		  0x40
#define MAPPER_GREEN_LED	  0x80

/**
 * @brief Get the value of the bank state.
 * 
 * @return The current bank state.
 */
__attribute__((leaf)) char get_bank_state(void);

/**
 * @brief Set the value of the bank state.
 * 
 * @param value The value to set the bank state to.
 * @return The previous bank state.
 */
__attribute__((leaf)) char set_bank_state(char value);

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
 * @return The previous bank state.
 */
__attribute__((leaf)) char set_prg_bank(char bank_id);

/**
 * @brief Enable/disable the red LED on the cartridge PCB.
 */
__attribute__((leaf)) char set_mapper_red_led(bool value);

/**
 * @brief Enable/disable the green LED on the cartridge PCB.
 */
__attribute__((leaf)) char set_mapper_green_led(bool value);

/**
 * @brief Switch to the given CHR bank immediately.
 *
 * @param bank_id The bank ID to switch to (0-1).
 */
__attribute__((leaf)) void set_chr_bank(char bank_id);

/**
 * @brief Switch to the given CHR bank at the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to (0-1).
 */
__attribute__((leaf)) void swap_chr_bank(char bank_id);

/**
 * @brief Switch to the given CHR bank until the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to (0-1).
 */
__attribute__((leaf)) void split_chr_bank(char bank_id);

/**
 * @brief Switch to the given nametable (NT) bank immediately.
 *
 * @param bank_id The bank ID to switch to (0-1).
 */
__attribute__((leaf)) void set_nt_bank(char bank_id);

/**
 * @brief Switch to the given nametable (NT) bank at the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to (0-1).
 */
__attribute__((leaf)) void swap_nt_bank(char bank_id);

/**
 * @brief Switch to the given nametable (NT) bank until the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to (0-1).
 */
__attribute__((leaf)) void split_nt_bank(char bank_id);

#ifdef __cplusplus
}
#endif

#endif // _MAPPER_H_
