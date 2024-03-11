// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_GRAPHICS_H
#define _NEO_GRAPHICS_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the global graphics system settings.
 */
__attribute__((leaf))
void neo_graphics_set_defaults(uint8_t color_mask, uint8_t color_xor, uint8_t fill, uint8_t extent, uint8_t flip);

/**
 * @brief Draw a line.
 *
 * @param x1 Begin X
 * @param y1 Begin Y
 * @param x2 End X
 * @param y2 End Y
 */
__attribute__((leaf))
void neo_graphics_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * @brief Draw a rectangle.
 *
 * @param x1 Begin X
 * @param y1 Begin Y
 * @param x2 End X
 * @param y2 End Y
 */
__attribute__((leaf))
void neo_graphics_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * @brief Draw an ellipse.
 *
 * @param x1 Begin X
 * @param y1 Begin Y
 * @param x2 End X
 * @param y2 End Y
 */
__attribute__((leaf))
void neo_graphics_draw_ellipse(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * @brief Draw a pixel.
 *
 * @param x X
 * @param y Y
 */
__attribute__((leaf))
void neo_graphics_draw_pixel(uint16_t x, uint16_t y);

// FIXME: neo_graphics_draw_text

/**
 * @brief Draw an image.
 *
 * @param x X
 * @param y Y
 * @param id Image ID
 */
__attribute__((leaf))
void neo_graphics_draw_image(uint16_t x, uint16_t y, uint8_t id);

/**
 * @brief Draw the current tilemap.
 *
 * @param x1 Begin X
 * @param y1 Begin Y
 * @param x2 End X
 * @param y2 End Y
 */
__attribute__((leaf))
void neo_graphics_draw_tilemap(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * @brief Set palette color.
 *
 * @param idx Palette index.
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
__attribute__((leaf))
void neo_graphics_set_palette(uint8_t idx, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Read pixel.
 *
 * @param x X
 * @param y Y
 * @return The pixel palette index.
 */
__attribute__((leaf))
uint8_t neo_graphics_read_pixel(uint16_t x, uint16_t y);

/**
 * @brief Reset palette.
 */
__attribute__((leaf))
void neo_graphics_reset_palette(void);

/**
 * @brief Set the current tilemap.
 *
 * @param src Tilemap address.
 * @param x X offset into tilemap.
 * @param y Y offset into tilemap.
 */
__attribute__((leaf))
void neo_graphics_set_tilemap(const void *src, uint16_t x, uint16_t y);

/**
 * @brief Read the number of vertical blanks since power-on.
 */
__attribute__((leaf))
long neo_graphics_frame_count(void);

/**
 * @brief Set the current drawing color.
 *
 * @param idx Palette index.
 */
__attribute__((leaf))
void neo_graphics_set_color(uint8_t idx);

/**
 * @brief Set the current solid flag.
 *
 * @param value Value.
 */
__attribute__((leaf))
void neo_graphics_set_solid_flag(uint8_t value);

/**
 * @brief Set the current image/font drawing scale.
 *
 * @param value Value.
 */
__attribute__((leaf))
void neo_graphics_set_draw_size(uint8_t value);

/**
 * @brief Set the flip bits for drawing images.
 *
 * @param value Value.
 */
__attribute__((leaf))
void neo_graphics_set_flip_bits(uint8_t value);

#ifdef __cplusplus
}
#endif

#endif
