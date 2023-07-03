/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_PSG_H_
#define _PCE_PSG_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file psg.h
 * Functionality related to the PSG.
 */

/**
 * @brief Reset the PSG.
 */
void pce_psg_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* _PCE_PSG_H_ */
