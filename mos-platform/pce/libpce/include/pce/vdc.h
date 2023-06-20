/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_VDC_H_
#define _PCE_VDC_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file vdc.h
 * Functionality related to the VDC.
 */

/**
 * @brief Read a value from the VDC port.
 * 
 * @param index Register to read.
 * @return uint16_t Value read.
 */
uint16_t pce_vdc_peek(uint8_t index);

/**
 * @brief Write a value to the VDC port.
 * 
 * @param index Register to write.
 * @param data Value to write.
 */
void pce_vdc_poke(uint8_t index, uint16_t data);

/**
 * @brief Set the VDC width, in tiles.
 * 
 * @param tiles The number of tiles.
 * @param vce_flags VCE control register configuration:
 *  - VCE_FIELD_ODD
 *  - VCE_COLORBURST_OFF
 */
void pce_vdc_set_width_tiles(uint8_t tiles, uint8_t vce_flags);
#define pce_vdc_set_width(pixels, vce_flags) pce_vdc_set_width_tiles((pixels) >> 3, vce_flags)

/**
 * @brief Set the VDC height, in raster lines.
 * 
 * @param lines The number of raster lines.
 */
void pce_vdc_set_height(uint8_t lines);
#define pce_vdc_set_size(width_pixels, height_pixels, vce_flags) \
    pce_vdc_set_width(width_pixels, vce_flags); \
    pce_vdc_set_height(height_pixels)

#ifdef __cplusplus
}
#endif

#endif /* _PCE_VDC_H_ */