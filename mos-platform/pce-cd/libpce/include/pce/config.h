/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_CONFIG_H_
#define _PCE_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file config.h
 * Functionality related to output ELF configuration.
 */

#define __PCE_CARD_BANK_DECLARE(id, offset, size) \
asm(".global __card_bank" #id "\n.global __card_bank" #id "_size\n.equ __card_bank" #id ", ((" #offset ") << 13)\n.equ __card_bank" #id "_size, ((" #size ") << 13)\n")

#define __PCE_CARD_BANK_USE(id, offset) \
static inline void pce_card_bank ## id ## _map(void) { \
    __attribute__((leaf)) asm volatile ( \
        "lda #mos8(__card_bank" #id "_bank)\n" \
        "tam #(1 << " #offset ")\n" : : : "a", "p" ); \
}

#define __PCE_CARD_BANK_CALLBACK_DECLARE(id, offset) \
__attribute__((leaf, callback(1), noinline, section("text.pce_card_bank" #id "_call"))) \
void pce_card_bank ## id ## _call(void (*method)(void)) { \
    pce_bank ## offset ## _size1_push(); \
    pce_card_bank ## id ## _map(); \
    method(); \
    pce_bank ## offset ## _size1_pop(); \
}

#define __PCE_CARD_BANK_CALLBACK_USE(id) \
__attribute__((leaf, callback(1))) \
void pce_card_bank ## id ## _call(void (*method)(void))

#ifdef PCE_CONFIG_IMPLEMENTATION
#define PCE_CARD_BANK_AT(id, offset) \
__PCE_CARD_BANK_DECLARE(id, offset, 1); \
__PCE_CARD_BANK_USE(id, offset) \
__PCE_CARD_BANK_CALLBACK_DECLARE(id, offset)
#define PCE_CDB_USE_PSG_DRIVER(value) \
asm(".global __pce_cdb_use_psg\n.equ __pce_cdb_use_psg, " #value "\n")
#define PCE_CDB_USE_GRAPHICS_DRIVER(value) \
asm(".global __pce_cdb_use_graphics\n.equ __pce_cdb_use_graphics, " #value "\n")
#else
/**
 * @brief Define the memory offset for a given physical bank.
 * 
 * A virtual bank is a group of one or more physical banks, automatically
 * allocated by the linker.
 *
 * The recommended way to define virtual banks is to create a header file
 * (for example, "bank.h") with PCE_CARD_BANK_AT entries, and a source
 * file ("bank.c") which defines PCE_CONFIG_IMPLEMENTATION, then
 * includes <pce.h>, then includes "bank.h".
 *
 * A bank N defined in this manner provides:
 * - the pce_card_bankN_map() function, mapping the requested virtual bank,
 * - the pce_card_bankN_call(void (*method)(void)) function defines a safe
 *   trampoline to a function in another bank,
 * - the __card_bankN section.
 *
 * @param id The ID of the physical bank (0-127).
 * @param offset The memory offset, in 8KB units (2-6).
 */
#define PCE_CARD_BANK_AT(id, offset) \
__PCE_CARD_BANK_USE(id, offset) \
__PCE_CARD_BANK_CALLBACK_USE(id)
/**
 * @brief Set to 1 to enable using the BIOS PSG driver. This reserves
 * additional console RAM (6 bytes ZP, 838 bytes RAM).
 */
#define PCE_CDB_USE_PSG_DRIVER(value)
/**
 * @brief Set to 1 to enable using the BIOS graphics driver. This reserves
 * additional console RAM (10 bytes ZP, 51 bytes RAM).
 */
#define PCE_CDB_USE_GRAPHICS_DRIVER(value)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PCE_CONFIG_H_ */
