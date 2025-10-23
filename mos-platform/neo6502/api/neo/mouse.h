// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdbool.h>
#include <stdint.h>

#ifndef _NEO_MOUSE_H
#define _NEO_MOUSE_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Move display cursor.
 */
void neo_mouse_move_display_cursor(uint16_t x, uint16_t y);

/**
 * @brief Get mouse display cursor on/off.
 */
void neo_mouse_set_mouse_display_cursor(uint8_t onOff);

/**
 * @brief Get mouse state.
 */
void neo_mouse_get_mouse_state(uint16_t *xPos, uint16_t *yPos,
                               uint8_t *buttonState,
                               uint8_t *scrollWheelState);

/**
 * @brief test mouse present.
 */
uint8_t neo_mouse_test_mouse_present(void);

/**
 * @brief select mouse cursor.
 */
// note: this API call can set error status; see neo_api_error() 
void neo_mouse_select_mouse_cursor(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif
