/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_CD_TYPES_H_
#define _PCE_CD_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file types.h
 * CD-related types.
 */

typedef struct pce_sector {
    union {
        struct {
            uint8_t track, track_end;
        };
        struct {
            uint8_t frame, second, minute;
        };
        struct {
            uint8_t lo, md, hi;
        };
    };
} pce_sector_t;

#ifdef __cplusplus
}
#endif

#endif /* _PCE_CD_TYPES_H_ */
