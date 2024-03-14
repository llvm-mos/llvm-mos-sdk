// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_TURTLE_H
#define _NEO_TURTLE_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialise the turtle graphics system.
 *
 * @param idx Sprite index to use for the turtle.
 */
void neo_turtle_init(uint8_t idx);

/**
 * @brief Turn the turtle right. Show if hidden.
 *
 * @param deg Degrees.
 */
void neo_turtle_turn(int16_t deg);

/**
 * @brief Move the turtle forward. Show if hidden.
 *
 * @param len Pixels to move.
 * @param color Color to draw.
 * @param pen Pen down flag.
 */
void neo_turtle_move(int16_t len, uint8_t color, uint8_t pen);

/**
 * @brief Hide the turtle.
 */
void neo_turtle_hide(void);

/**
 * @brief Move the turtle to the home position - centered, facing upward.
 */
void neo_turtle_home(void);

#ifdef __cplusplus
}
#endif

#endif
