// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>
#include <string.h>
#include "neo/types.h"

#ifndef _NEO_API_INTERNAL_H
#define _NEO_API_INTERNAL_H

typedef struct neo_pstring neo_pstring_t;

/**
 * @brief Given an input C-format string FROM, provide a Pascal-format string FROM_p using VLAs.
 */
#define PASCALIZE_INPUT(FROM, TO) \
    uint8_t FROM ## _len = strlen(FROM); \
    char TO[FROM ## _len+1]; \
    TO[0] = FROM ## _len; \
    memcpy(TO + 1, FROM, FROM ## _len)

/**
 * @brief Given an input Pascal-format string to, convert it in place to a C-format string.
 */
void __neo_depascalize_output(char *to);

#endif
