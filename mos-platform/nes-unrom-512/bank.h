// Copyright 2023 LLVM-MOS Project
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
 * @brief Define this in a .c file to use 1-screen switchable mirroring.
 */
#define MAPPER_USE_1_SCREEN \
	asm(".globl __mirroring\n.globl __four_screen\n__mirroring = 0\n__four_screen = 1\n")

/**
 * @brief Define this in a .c file to use 4-screen mirroring, with the last
 * 8 KB of CHR-RAM dedicated to storing the four name tables.
 *
 * In this mode, only banks 0-2 of CHR-RAM are fully safe to use for pattern
 * table data.
 */
#define MAPPER_USE_4_SCREEN_NAMETABLE \
	asm(".globl __mirroring\n.globl __four_screen\n__mirroring = 1\n__four_screen = 1\n")

/**
 * @brief Define this in a .c file to use the self-flashable board.
 *
 * This also protects against bus conflicts, removing the bus conflict table
 * from the fixed ROM bank.
 */
#define MAPPER_USE_SELF_FLASHABLE_BOARD \
	asm(".globl __battery\n__battery = 1\n")

#define PRG_BANK_MASK       0x1F
#define PRG_BANK_SHIFT      0
#define CHR_BANK_MASK       0x60
#define CHR_BANK_SHIFT      5
#define CHR_BANK(n)	      ((n) << 5)
#define CHR_BANK_0	      CHR_BANK(0)
#define CHR_BANK_1	      CHR_BANK(1)
#define CHR_BANK_2	      CHR_BANK(2)
#define CHR_BANK_3	      CHR_BANK(3)
#define MIRROR_SCREEN_MASK  0x80
#define MIRROR_SCREEN_SHIFT 7
#define MIRROR_SCREEN_1     0x00
#define MIRROR_SCREEN_2     0x80

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
 * @brief Switch to the given CHR bank immediately.
 *
 * @param bank_id The bank ID to switch to (0-3).
 */
__attribute__((leaf)) void set_chr_bank(char bank_id);

/**
 * @brief Switch to the given CHR bank at the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to (0-3).
 */
__attribute__((leaf)) void swap_chr_bank(char bank_id);

/**
 * @brief Switch to the given CHR bank until the next NMI.
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param bank_id The bank ID to switch to (0-3).
 */
__attribute__((leaf)) void split_chr_bank(char bank_id);

/**
 * @brief Switch to the given mirrored screen immediately.
 * This is only effective under @ref MAPPER_USE_1_SCREEN .
 *
 * @param screen_id The mirrored screen to switch to (0-1).
 */
__attribute__((leaf)) void set_mirrored_screen(char screen_id);

/**
 * @brief Switch to the given mirrored screen at the next NMI.
 * This is only effective under @ref MAPPER_USE_1_SCREEN .
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param screen_id The mirrored screen to switch to (0-1).
 */
__attribute__((leaf)) void swap_mirrored_screen(char screen_id);

/**
 * @brief Switch to the given mirrored screen until the next NMI.
 * This is only effective under @ref MAPPER_USE_1_SCREEN .
 * This function will only work correctly if NMI generation is enabled
 * (PPUCTRL bit 7).
 *
 * @param screen_id The mirrored screen to switch to (0-1).
 */
__attribute__((leaf)) void split_mirrored_screen(char screen_id);

#ifdef __cplusplus
}
#endif

#endif // _BANK_H_
