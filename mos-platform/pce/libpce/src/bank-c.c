/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include "pce/hardware.h"

__attribute__((leaf)) uint8_t pce_bank0_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #1" : "=a"(result) : : );
    return result;
}

void pce_bank0_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #1" : "+a"(id) : : );
}
void pce_bank0_size1_set(uint8_t id) __attribute__((alias ("pce_bank0_set")));
void pce_bank0_size1i_set(uint8_t id) __attribute__((alias ("pce_bank0_set")));

__attribute__((leaf)) uint8_t pce_bank1_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #2" : "=a"(result) : : );
    return result;
}

void pce_bank1_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #2" : "+a"(id) : : );
}
void pce_bank1_size1_set(uint8_t id) __attribute__((alias ("pce_bank1_set")));
void pce_bank1_size1i_set(uint8_t id) __attribute__((alias ("pce_bank1_set")));

__attribute__((leaf)) uint8_t pce_bank2_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #4" : "=a"(result) : : );
    return result;
}

void pce_bank2_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #4" : "+a"(id) : : );
}
void pce_bank2_size1_set(uint8_t id) __attribute__((alias ("pce_bank2_set")));
void pce_bank2_size1i_set(uint8_t id) __attribute__((alias ("pce_bank2_set")));

__attribute__((leaf)) uint8_t pce_bank3_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #8" : "=a"(result) : : );
    return result;
}

void pce_bank3_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #8" : "+a"(id) : : );
}
void pce_bank3_size1_set(uint8_t id) __attribute__((alias ("pce_bank3_set")));
void pce_bank3_size1i_set(uint8_t id) __attribute__((alias ("pce_bank3_set")));

__attribute__((leaf)) uint8_t pce_bank4_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #16" : "=a"(result) : : );
    return result;
}

void pce_bank4_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #16" : "+a"(id) : : );
}
void pce_bank4_size1_set(uint8_t id) __attribute__((alias ("pce_bank4_set")));
void pce_bank4_size1i_set(uint8_t id) __attribute__((alias ("pce_bank4_set")));

__attribute__((leaf)) uint8_t pce_bank5_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #32" : "=a"(result) : : );
    return result;
}

void pce_bank5_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #32" : "+a"(id) : : );
}
void pce_bank5_size1_set(uint8_t id) __attribute__((alias ("pce_bank5_set")));
void pce_bank5_size1i_set(uint8_t id) __attribute__((alias ("pce_bank5_set")));

__attribute__((leaf)) uint8_t pce_bank6_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #64" : "=a"(result) : : );
    return result;
}

void pce_bank6_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #64" : "+a"(id) : : );
}
void pce_bank6_size1_set(uint8_t id) __attribute__((alias ("pce_bank6_set")));
void pce_bank6_size1i_set(uint8_t id) __attribute__((alias ("pce_bank6_set")));

__attribute__((leaf)) uint8_t pce_bank7_get(void) {
    uint8_t result;
    __attribute__((leaf)) asm volatile(
        "tma #128" : "=a"(result) : : );
    return result;
}

void pce_bank7_set(uint8_t id) {
    __attribute__((leaf)) asm volatile(
        "tam #128" : "+a"(id) : : );
}
void pce_bank7_size1_set(uint8_t id) __attribute__((alias ("pce_bank7_set")));
void pce_bank7_size1i_set(uint8_t id) __attribute__((alias ("pce_bank7_set")));