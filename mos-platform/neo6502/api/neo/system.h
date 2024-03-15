// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_SYSTEM_H
#define _NEO_SYSTEM_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Return the error code, if any.
 *
 * @return Non-zero if an error has occured.
 */
uint8_t neo_api_error(void);

/**
 * @brief Query the value of the 100Hz system timer.
 *
 * @return Current system timer value.
 */
long neo_system_timer(void);

/**
 * @brief Query the state of the specific keyboard key.
 *
 * @param key Key to query.
 * @return Key status.
 */
uint8_t neo_system_key_status(char key);

/**
 * @brief Print the Neo6502 project contributors.
 */
void neo_system_credits(void);

/**
 * @brief Update the serial command handler.
 */
void neo_system_serial_update(void);

/**
 * @brief Set the locale code.
 *
 * @param locale Locale code, for example "EN" or "FR".
 */
void neo_system_locale(const char *locale);

/**
 * @brief Reset the Neo6502.
 */
__attribute__((leaf, noreturn))
void neo_system_reset(void);

#ifdef __cplusplus
}
#endif

#endif
