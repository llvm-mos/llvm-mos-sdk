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

__attribute__((leaf)) uint8_t pce_bank0_get(void);
__attribute__((leaf)) void pce_bank0_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank1_get(void);
__attribute__((leaf)) void pce_bank1_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank2_get(void);
__attribute__((leaf)) void pce_bank2_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank3_get(void);
__attribute__((leaf)) void pce_bank3_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank4_get(void);
__attribute__((leaf)) void pce_bank4_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank5_get(void);
__attribute__((leaf)) void pce_bank5_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank6_get(void);
__attribute__((leaf)) void pce_bank6_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank7_get(void);
__attribute__((leaf)) void pce_bank7_set(uint8_t id);
__attribute__((leaf)) void pce_bank23i_set(uint8_t id);
__attribute__((leaf)) void pce_bank234i_set(uint8_t id);
__attribute__((leaf)) void pce_bank2345i_set(uint8_t id);
__attribute__((leaf)) void pce_bank23456i_set(uint8_t id);
__attribute__((leaf)) void pce_bank34i_set(uint8_t id);
__attribute__((leaf)) void pce_bank345i_set(uint8_t id);
__attribute__((leaf)) void pce_bank3456i_set(uint8_t id);
__attribute__((leaf)) void pce_bank45i_set(uint8_t id);
__attribute__((leaf)) void pce_bank456i_set(uint8_t id);
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
#define PCE_RAM_SGX(size) \
asm(".global __ram_bank_size\n.equ __ram_bank_size, ((" #size ") << 13)\n")
#else
#define PCE_ROM_VBANK_DEFINE(id, offset, size) \
PCE_VBANK_USE(rom, id, offset, size) \
PCE_VBANK_CALLBACK_USE(id)
#define PCE_RAM_SGX(size)
#endif


#endif /* _PCE_BANK_H_ */
