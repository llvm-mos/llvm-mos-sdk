// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_CONTROLLER_H
#define _NEO_CONTROLLER_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read the default controller's status.
 */
uint8_t neo_controller_read_default(void);

/**
 * @brief Read the connected controller count.
 */
uint8_t neo_controller_count(void);

/**
 * @brief Read the specified controller's status.
 */
uint32_t neo_controller_read(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif
