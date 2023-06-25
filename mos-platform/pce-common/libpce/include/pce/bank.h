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

#ifdef __cplusplus
extern "C" {
#endif

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

static inline void pce_bank2_size1_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$04\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank2_size1_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$04\n"
        "" : : : "a");
}

static inline void pce_bank2_size2_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$04\n"
        "pha\n"
        "tma #$08\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank2_size2_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$08\n"
        "pla\n"
        "tam #$04\n"
        "" : : : "a");
}

static inline void pce_bank2_size3_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$04\n"
        "pha\n"
        "tma #$08\n"
        "pha\n"
        "tma #$10\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank2_size3_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$10\n"
        "pla\n"
        "tam #$08\n"
        "pla\n"
        "tam #$04\n"
        "" : : : "a");
}

static inline void pce_bank2_size4_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$04\n"
        "pha\n"
        "tma #$08\n"
        "pha\n"
        "tma #$10\n"
        "pha\n"
        "tma #$20\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank2_size4_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$20\n"
        "pla\n"
        "tam #$10\n"
        "pla\n"
        "tam #$08\n"
        "pla\n"
        "tam #$04\n"
        "" : : : "a");
}

static inline void pce_bank2_size5_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$04\n"
        "pha\n"
        "tma #$08\n"
        "pha\n"
        "tma #$10\n"
        "pha\n"
        "tma #$20\n"
        "pha\n"
        "tma #$40\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank2_size5_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$40\n"
        "pla\n"
        "tam #$20\n"
        "pla\n"
        "tam #$10\n"
        "pla\n"
        "tam #$08\n"
        "pla\n"
        "tam #$04\n"
        "" : : : "a");
}

static inline void pce_bank3_size1_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$08\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank3_size1_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$08\n"
        "" : : : "a");
}

static inline void pce_bank3_size2_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$08\n"
        "pha\n"
        "tma #$10\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank3_size2_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$10\n"
        "pla\n"
        "tam #$08\n"
        "" : : : "a");
}

static inline void pce_bank3_size3_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$08\n"
        "pha\n"
        "tma #$10\n"
        "pha\n"
        "tma #$20\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank3_size3_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$20\n"
        "pla\n"
        "tam #$10\n"
        "pla\n"
        "tam #$08\n"
        "" : : : "a");
}

static inline void pce_bank3_size4_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$08\n"
        "pha\n"
        "tma #$10\n"
        "pha\n"
        "tma #$20\n"
        "pha\n"
        "tma #$40\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank3_size4_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$40\n"
        "pla\n"
        "tam #$20\n"
        "pla\n"
        "tam #$10\n"
        "pla\n"
        "tam #$08\n"
        "" : : : "a");
}

static inline void pce_bank4_size1_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$10\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank4_size1_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$10\n"
        "" : : : "a");
}

static inline void pce_bank4_size2_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$10\n"
        "pha\n"
        "tma #$20\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank4_size2_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$20\n"
        "pla\n"
        "tam #$10\n"
        "" : : : "a");
}

static inline void pce_bank4_size3_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$10\n"
        "pha\n"
        "tma #$20\n"
        "pha\n"
        "tma #$40\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank4_size3_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$40\n"
        "pla\n"
        "tam #$20\n"
        "pla\n"
        "tam #$10\n"
        "" : : : "a");
}

static inline void pce_bank5_size1_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$20\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank5_size1_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$20\n"
        "" : : : "a");
}

static inline void pce_bank5_size2_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$20\n"
        "pha\n"
        "tma #$40\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank5_size2_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$40\n"
        "pla\n"
        "tam #$20\n"
        "" : : : "a");
}

static inline void pce_bank6_size1_push(void) {
    __attribute__((leaf)) asm volatile (
        "tma #$40\n"
        "pha\n"
        "" : : : "a");
}

static inline void pce_bank6_size1_pop(void) {
    __attribute__((leaf)) asm volatile (
        "pla\n"
        "tam #$40\n"
        "" : : : "a");
}

#define PCE_BANK_MASK(n) (1 << (n))
#define PCE_BANK_OFFSET(n) ((n) << 13)
#define PCE_BANK_SIZE(n) ((n) << 13)

#define __PCE_ROM_BANK_DECLARE(id, offset, size) \
asm(".global __rom_bank" #id "\n.global __rom_bank" #id "_size\n.equ __rom_bank" #id ", ((" #offset ") << 13)\n.equ __rom_bank" #id "_size, ((" #size ") << 13)\n")

#define __PCE_ROM_BANK_USE(id, offset) \
static inline void pce_rom_bank ## id ## _map(void) { \
    __attribute__((leaf)) asm volatile ( \
        "lda #mos8(__rom_bank" #id "_bank)\n" \
        "tam #(1 << " #offset ")\n" : : : "a", "p" ); \
}

#define __PCE_ROM_BANK_CALLBACK_DECLARE(id, offset) \
__attribute__((leaf, callback(1), noinline, section("text.pce_rom_bank" #id "_call"))) \
void pce_rom_bank ## id ## _call(void (*method)(void)) { \
    pce_bank ## offset ## _size1_push(); \
    pce_rom_bank ## id ## _map(); \
    method(); \
    pce_bank ## offset ## _size1_pop(); \
}

#define __PCE_ROM_BANK_CALLBACK_USE(id) \
__attribute__((leaf, callback(1))) \
void pce_rom_bank ## id ## _call(void (*method)(void))

#ifdef PCE_CONFIG_IMPLEMENTATION
#define PCE_ROM_BANK_AT(id, offset) \
__PCE_ROM_BANK_DECLARE(id, offset, 1); \
__PCE_ROM_BANK_USE(id, offset) \
__PCE_ROM_BANK_CALLBACK_DECLARE(id, offset)
#define PCE_ROM_FIXED_BANK_SIZE(size) \
__PCE_ROM_BANK_DECLARE(0, 8 - size, size)
#define PCE_SGX_RAM(size) \
asm(".global __ram_bank_size\n.equ __ram_bank_size, ((" #size ") << 13)\n")
#else
/**
 * @brief Define the memory offset for a given physical bank.
 * 
 * A virtual bank is a group of one or more physical banks, automatically
 * allocated by the linker.
 *
 * The recommended way to define virtual banks is to create a header file
 * (for example, "bank.h") with PCE_ROM_BANK_AT entries, and a source
 * file ("bank.c") which defines PCE_CONFIG_IMPLEMENTATION, then
 * includes <pce.h>, then includes "bank.h".
 *
 * A bank N defined in this manner provides:
 * - the pce_rom_bankN_map() function, mapping the requested virtual bank,
 * - the pce_rom_bankN_call(void (*method)(void)) function defines a safe
 *   trampoline to a function in another bank,
 * - the __rom_bankN section.
 *
 * @param id The ID of the physical bank (0-127).
 * @param offset The memory offset, in 8KB units (2-6).
 */
#define PCE_ROM_BANK_AT(id, offset) \
__PCE_ROM_BANK_USE(id, offset) \
__PCE_ROM_BANK_CALLBACK_USE(id)
/**
 * @brief Define the size of the fixed bank (at the top of memory).
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

#ifdef __cplusplus
}
#endif

#endif /* _PCE_BANK_H_ */
