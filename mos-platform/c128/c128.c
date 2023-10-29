/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#define __CBM__
#include <cbm.h>
#define __C128__
#include <c128.h>

#define MODE (*((volatile uint8_t*) 0xD7))

extern void __C64MODE(void) __attribute__((leaf, noreturn));
extern void __SWAPPER(void) __attribute__((leaf));

unsigned char videomode(unsigned char mode) {
    unsigned char lastmode = MODE;
    if (lastmode != mode) {
        __SWAPPER(); // Swap video modes
    }
    return lastmode;
}

__attribute__((noreturn))
void c64mode(void) {
    __C64MODE();
}

void fast(void) {
    VIC.clock = 1;
}

void slow(void) {
    VIC.clock = 0;
}

unsigned char isfast(void) {
    return VIC.clock & 0x01;
}
