// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Mapper functions for multiple-area bank switching schemes.
// (E0, EC)

#ifndef _MAPPER_ROM_MULTI_H_
#define _MAPPER_ROM_MULTI_H_

#ifdef __cplusplus
extern "C" {
#endif

// ROM bank index type.
typedef unsigned char rom_bank_t;
typedef unsigned char banked_area_t;

// Switch in a ROM bank into a given area.
__attribute__((weak, leaf)) void bank_select(
    banked_area_t area,
    rom_bank_t bank_id);

#ifdef __cplusplus
}
#endif

#endif
