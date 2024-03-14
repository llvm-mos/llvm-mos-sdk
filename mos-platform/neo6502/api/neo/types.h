// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_TYPES_H
#define _NEO_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct neo_pstring {
    uint8_t length;
    char data[];
} neo_pstring_t;

#ifdef __cplusplus
}
#endif

#endif
