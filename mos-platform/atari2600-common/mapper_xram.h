// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MAPPER_XRAM_H_
#define _MAPPER_XRAM_H_

#include <mapper_base.h>

#ifdef __cplusplus
extern "C" {
#endif

// Macro to declare a variable in XRAM.
// - index = bank index
// - declaration = variable declaration
// This will declare two variables, one read-only and one write-only.
// For example, DECLARE_XRAM_VARIABLE(0, int my_var)
// creates two variables: my_var_read and my_var_write.
#define DECLARE_XRAM_VARIABLE(index, declaration) \
    __attribute__((section(".xram" #index "_read"))) volatile const declaration##_read; \
    __attribute__((section(".xram" #index "_write"))) volatile declaration##_write;

// Switch in a RAM bank.
__attribute__((weak, leaf)) void ram_select(bank_index_t bank_id);

// Switch to another RAM bank and call this function.
__attribute__((callback(2))) void banked_call_ram(bank_index_t bankId,
                                                        void (*method)(void));

// Write a byte to extended RAM at set offset
// RAM must be selected first, or use banked_call_ram
__attribute__((leaf)) void xram_write(int offset, unsigned char value);

// Read a byte from extended RAM at set offset
// RAM must be selected first, or use banked_call_ram
__attribute__((leaf)) unsigned char xram_read(int offset);

#ifdef __cplusplus
}
#endif

#endif // _MAPPER_H_
