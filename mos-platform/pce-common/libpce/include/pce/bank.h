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

#ifdef __cplusplus
}
#endif

#endif /* _PCE_BANK_H_ */
