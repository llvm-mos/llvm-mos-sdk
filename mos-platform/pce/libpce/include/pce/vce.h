/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_VCE_H_
#define _PCE_VCE_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file vce.h
 * Functionality related to the VCE.
 */

#define VCE_COLOR_INDEX(index, color) (((uint16_t) (index) << 4) + color)

/**
 * @brief Get a color from the VCE.
 * 
 * @param index The color index - @ref VCE_COLOR_INDEX
 * @return uint16_t The color value.
 */
uint16_t pce_vce_get_color(uint16_t index);
/**
 * @brief Set a color to the VCE.
 * 
 * @param index The color index - @ref VCE_COLOR_INDEX
 * @param value The color value.
 */
void pce_vce_set_color(uint16_t index, uint16_t value);

/**
 * @brief Copy palettes (N x 16 colors) from RAM to the VCE.
 * 
 * @param index Destination palette index, from 0 to 31.
 * @param source Source memory address.
 * @param count Palette count, from 1 to 32.
 */
void pce_vce_copy_palette(uint8_t index, const void *source, uint8_t count);

/**
 * @brief Copy palettes (N x 16 colors) from the VCE to RAM.
 * 
 * @param dest Destination memory address.
 * @param index Source palette index, from 0 to 31.
 * @param count Palette count, from 1 to 32.
 */
void pce_vce_copy_palette_to_ram(void *dest, uint8_t index, uint8_t count);

#ifdef __cplusplus
}
#endif

#endif /* _PCE_VCE_H_ */