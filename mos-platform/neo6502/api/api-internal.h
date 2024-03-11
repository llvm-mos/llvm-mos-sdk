// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>
#include <string.h>

#ifndef _NEO_API_INTERNAL_H
#define _NEO_API_INTERNAL_H

/**
 * @brief Given an input C-format string FROM, provide a Pascal-format string FROM_p using VLAs.
 */
#define PASCALIZE_INPUT(FROM) \
    uint8_t FROM ## _len = strlen(FROM); \
    char FROM ## _p[FROM ## _len+1]; \
    FROM ## _p[0] = FROM ## _len; \
    memcpy(FROM ## _p + 1, FROM, FROM ## _len)

/**
 * @brief Given an input Pascal-format string to, convert it in place to a C-format string.
 */
void __neo_depascalize_output(char *to);

#endif
