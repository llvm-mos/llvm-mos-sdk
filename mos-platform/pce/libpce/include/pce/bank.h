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
__attribute__((leaf)) void pce_bank0i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank1_get(void);
__attribute__((leaf)) void pce_bank1_set(uint8_t id);
__attribute__((leaf)) void pce_bank1i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank2_get(void);
__attribute__((leaf)) void pce_bank2_set(uint8_t id);
__attribute__((leaf)) void pce_bank2i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank3_get(void);
__attribute__((leaf)) void pce_bank3_set(uint8_t id);
__attribute__((leaf)) void pce_bank3i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank4_get(void);
__attribute__((leaf)) void pce_bank4_set(uint8_t id);
__attribute__((leaf)) void pce_bank4i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank5_get(void);
__attribute__((leaf)) void pce_bank5_set(uint8_t id);
__attribute__((leaf)) void pce_bank5i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank6_get(void);
__attribute__((leaf)) void pce_bank6_set(uint8_t id);
__attribute__((leaf)) void pce_bank6i_set(uint8_t id);
__attribute__((leaf)) uint8_t pce_bank7_get(void);
__attribute__((leaf)) void pce_bank7_set(uint8_t id);
__attribute__((leaf)) void pce_bank7i_set(uint8_t id);
__attribute__((leaf)) void pce_bank23_set(uint8_t id);
__attribute__((leaf)) void pce_bank23i_set(uint8_t id);
__attribute__((leaf)) void pce_bank234_set(uint8_t id);
__attribute__((leaf)) void pce_bank234i_set(uint8_t id);
__attribute__((leaf)) void pce_bank2345_set(uint8_t id);
__attribute__((leaf)) void pce_bank2345i_set(uint8_t id);
__attribute__((leaf)) void pce_bank23456_set(uint8_t id);
__attribute__((leaf)) void pce_bank23456i_set(uint8_t id);
__attribute__((leaf)) void pce_bank34_set(uint8_t id);
__attribute__((leaf)) void pce_bank34i_set(uint8_t id);
__attribute__((leaf)) void pce_bank345_set(uint8_t id);
__attribute__((leaf)) void pce_bank345i_set(uint8_t id);
__attribute__((leaf)) void pce_bank3456_set(uint8_t id);
__attribute__((leaf)) void pce_bank3456i_set(uint8_t id);
__attribute__((leaf)) void pce_bank45_set(uint8_t id);
__attribute__((leaf)) void pce_bank45i_set(uint8_t id);
__attribute__((leaf)) void pce_bank456_set(uint8_t id);
__attribute__((leaf)) void pce_bank456i_set(uint8_t id);
__attribute__((leaf)) void pce_bank56_set(uint8_t id);
__attribute__((leaf)) void pce_bank56i_set(uint8_t id);

#define PCE_BANK_OFFSET(n) ((n) << 13)
#define PCE_BANK_SIZE(n) ((n) << 13)

#define PCE_VBANK_USE(id, offset, size) \
static inline void pce_vbank ## id ## _set(void) { \
    __attribute__((leaf)) asm volatile ( \
        "lda #mos8(__rom_" #id "_bank)\n" \
        "jsr pce_bank" #offset "_size" #size "i_set\n" \
    ); \
}

#define PCE_VBANK_DECLARE(id, offset, size) \
asm(".global __rom_" #id "_size\n.equ __rom_" #id "_offset, (" #offset " << 13)\n.equ __rom_" #id "_size, (" #size " << 13)\n")

#ifdef PCE_VBANK_IMPLEMENTATION
#define PCE_VBANK_DEFINE(id, offset, size) \
PCE_VBANK_DECLARE(id, offset, size); \
PCE_VBANK_USE(id, offset, size)
#else
#define PCE_VBANK_DEFINE(id, offset, size) \
PCE_VBANK_USE(id, offset, size)
#endif

#endif /* _PCE_BANK_H_ */