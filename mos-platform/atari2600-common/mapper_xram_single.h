// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Functions for single-area RAM bank switching schemes.
// (3E, E7)

#ifndef _MAPPER_XRAM_H_
#define _MAPPER_XRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

// RAM bank index type.
typedef unsigned char ram_bank_t;

// Macro to declare a variable in XRAM.
// - index = XRAM bank index
// - declaration = variable declaration
// This will declare two variables, one read-only and one write-only.
// For example, DECLARE_XRAM_VARIABLE(0, int my_var)
// creates two variables: my_var_read and my_var_write.
// NOTE: These variables are not initialized by default.
#define DECLARE_XRAM_VARIABLE(index, declaration) \
    __attribute__((section(".xram" #index "_read"))) volatile const declaration##_read; \
    __attribute__((section(".xram" #index "_write"))) volatile declaration##_write;

// Switch in a RAM bank.
void ram_select(ram_bank_t bank_id);

// Switch to another RAM bank and call this function.
__attribute__((callback(2))) void banked_call_ram(ram_bank_t bank_id,
                                                  void (*method)(void));

// Write a byte to extended RAM at set offset
// RAM must be selected first, or use banked_call_ram
void xram_write(int offset, unsigned char value);

// Read a byte from extended RAM at set offset
// RAM must be selected first, or use banked_call_ram
unsigned char xram_read(int offset);

#ifdef __cplusplus
}
#endif

#endif // _MAPPER_H_
