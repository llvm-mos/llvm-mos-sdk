// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdbool.h>
#include <stdint.h>

#ifndef _NEO_SPRITES_H
#define _NEO_SPRITES_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the sprite system.
 */
void neo_sprite_reset(void);

/**
 * @brief Set the sprite.
 *
 * @param id Sprite ID
 * @param x X position
 * @param y Y position
 * @param img Image paramemters
 * @param flip Flip axis
 * @param anchor Anchor value
 */
void neo_sprite_set(uint8_t id, uint16_t x, uint16_t y, uint8_t img, uint8_t flip, uint8_t anchor);

/**
 * @brief Hide the specified sprite.
 *
 * @param id Sprite ID
 */
void neo_sprite_hide(uint8_t id);

/**
 * @brief Check collision between two sprites.
 *
 * @param first First sprite ID
 * @param second Second sprite ID
 * @param distance Maximum distance between sprites
 */
bool neo_sprite_collision(uint8_t first, uint8_t second, uint8_t distance);

/**
 * @brief Get sprite position.
 *
 * @param id Sprite ID
 * @param x X position
 * @param y Y position
 */
void neo_sprite_position(uint8_t id, uint16_t *x, uint16_t *y);

#ifdef __cplusplus
}
#endif

#endif
