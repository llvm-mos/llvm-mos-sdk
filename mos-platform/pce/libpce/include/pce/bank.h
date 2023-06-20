/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_BANK_H_
#define _PCE_BANK_H_

#include <stdbool.h>
#include <stdint.h>

/** \file bank.h
 * Functionality related to cartridge banking.
 */

/**
 * @brief Get the currently mapped bank at offset 0.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank0_get(void);
/**
 * @brief Map a bank at offset 0.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank0_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 1.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank1_get(void);
/**
 * @brief Map a bank at offset 1.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank1_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 2.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank2_get(void);
/**
 * @brief Map a bank at offset 2.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank2_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 3.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank3_get(void);
/**
 * @brief Map a bank at offset 3.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank3_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 4.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank4_get(void);
/**
 * @brief Map a bank at offset 4.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank4_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 5.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank5_get(void);
/**
 * @brief Map a bank at offset 5.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank5_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 6.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank6_get(void);
/**
 * @brief Map a bank at offset 6.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank6_set(uint8_t id);
/**
 * @brief Get the currently mapped bank at offset 7.
 * @return The bank ID.
 */
__attribute__((leaf)) uint8_t pce_bank7_get(void);
/**
 * @brief Map a bank at offset 7.
 * @param id The bank ID to map.
 */
__attribute__((leaf)) void pce_bank7_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 2 to 3 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank23i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 2 to 4 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank234i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 2 to 5 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank2345i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 2 to 6 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank23456i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 3 to 4 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank34i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 3 to 5 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank345i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 3 to 6 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank3456i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 4 to 5 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank45i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 4 to 6 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank456i_set(uint8_t id);
/**
 * @brief Map consecutive banks at offsets from 5 to 6 inclusive.
 * @param id The first bank ID to map.
 */
__attribute__((leaf)) void pce_bank56i_set(uint8_t id);

#define PCE_BANK_MASK(n) (1 << (n))
#define PCE_BANK_OFFSET(n) ((n) << 13)
#define PCE_BANK_SIZE(n) ((n) << 13)

#define PCE_VBANK_USE_1(type, id, offset) \
static inline void pce_vbank ## id ## _set(void) { \
    __attribute__((leaf)) asm volatile ( \
        "lda #mos8(__" #type "_vbank_" #id "_bank)\n" \
        "tam #(1 << " #offset ")\n" : : : "a", "p" ); \
}

#define PCE_VBANK_USE_N(type, id, offset, size) \
static inline void pce_vbank ## id ## _set(void) { \
    __attribute__((leaf)) asm volatile ( \
        "lda #mos8(__" #type "_vbank_" #id "_bank)\n" \
        "jsr pce_bank" #offset "_size" #size "i_set\n" : : : "a", "p" ); \
}
#define PCE_VBANK_USE_2(type, id, offset) PCE_VBANK_USE_N(type, id, offset, 2)
#define PCE_VBANK_USE_3(type, id, offset) PCE_VBANK_USE_N(type, id, offset, 3)
#define PCE_VBANK_USE_4(type, id, offset) PCE_VBANK_USE_N(type, id, offset, 4)
#define PCE_VBANK_USE_5(type, id, offset) PCE_VBANK_USE_N(type, id, offset, 5)
#define PCE_VBANK_USE(type, id, offset, size) PCE_VBANK_USE_ ## size (type, id, offset)

#define PCE_VBANK_DECLARE(type, id, offset, size) \
asm(".global __" #type "_vbank_" #id "\n.global __" #type "_vbank_" #id "_size\n.equ __" #type "_vbank_" #id ", ((" #offset ") << 13)\n.equ __" #type "_vbank_" #id "_size, ((" #size ") << 13)\n")

#define PCE_VBANK_CALLBACK_DECLARE(id) \
__attribute__((leaf, callback(1), noinline, section("text.pce_vbank" #id "_call"))) \
void pce_vbank ## id ## _call(void (*method)(void)) { \
    pce_vbank ## id ## _set(); \
    method(); \
}

#define PCE_VBANK_CALLBACK_USE(id) \
__attribute__((leaf, callback(1))) \
void pce_vbank ## id ## _call(void (*method)(void))

#ifdef PCE_VBANK_IMPLEMENTATION
#define PCE_ROM_VBANK_DEFINE(id, offset, size) \
PCE_VBANK_DECLARE(rom, id, offset, size); \
PCE_VBANK_USE(rom, id, offset, size) \
PCE_VBANK_CALLBACK_DECLARE(id)
#define PCE_ROM_FIXED_BANK_SIZE(size) \
PCE_VBANK_DECLARE(rom, 0, 8 - size, size)
#define PCE_SGX_RAM(size) \
asm(".global __ram_bank_size\n.equ __ram_bank_size, ((" #size ") << 13)\n")
#else
/**
 * @brief Define a "virtual bank".
 * 
 * A virtual bank is a group of one or more physical banks, automatically
 * allocated by the linker.
 *
 * The recommended way to define virtual banks is to create a header file
 * (for example, "vbank.h") with PCE_ROM_VBANK_DEFINE entries, and a
 * source file ("vbank.c") which defines PCE_VBANK_IMPLEMENTATION, then
 * includes <pce.h>, then includes "vbank.h".
 *
 * A defined virtual bank N provides:
 * - the pce_vbankN_set() function, mapping the requested virtual bank,
 * - the pce_vbankN_call(void (*method)(void)) function, allowing a safe
 *   trampoline to a function in another bank,
 * - the __rom_vbank_N_bank symbol, allowing referencing the first bank
 *   of the virtual bank in assembly code.
 *
 * @param id The ID of the virtual bank.
 * @param offset The memory offset, in 8KB units (2-6).
 * @param size The size, in 8KB units (1-5).
 */
#define PCE_ROM_VBANK_DEFINE(id, offset, size) \
PCE_VBANK_USE(rom, id, offset, size) \
PCE_VBANK_CALLBACK_USE(id)
/**
 * @brief Define the size of the fixed bank ("virtual bank 0").
 * 
 * @param size The size, in 8KB units (1-6).
 */
#define PCE_ROM_FIXED_BANK_SIZE(size)
/**
 * @brief Define the amount of C RAM for SGX targets.
 *
 * The SGX provides up to 32 kilobytes of RAM in four banks (0xF8-0xFB),
 * but only one is mapped by default (at offset 0x2000), to preserve
 * compatibility with the standard PCE. Use this define in a source file
 * to map more RAM to C by default.
 *
 * Note that using this will reserve more banks for C RAM and the soft
 * stack; for example, PCE_SGX_RAM(2) will use bank offsets 1 *and* 2.
 *
 * @param size The size, in 8KB units (2-4).
 */
#define PCE_SGX_RAM(size)
#endif


#endif /* _PCE_BANK_H_ */
