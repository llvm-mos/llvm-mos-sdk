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

#define VDC_SPRITE_COLOR(n)     ((n))
#define VDC_SPRITE_COLOR_MASK   (0xF)
#define VDC_SPRITE_BG           0
#define VDC_SPRITE_FG           (0x1 << 7)
#define VDC_SPRITE_WIDTH_16     0
#define VDC_SPRITE_WIDTH_32     (0x1 << 8)
#define VDC_SPRITE_WIDTH_MASK   (0x1 << 8)
#define VDC_SPRITE_HEIGHT_16    0
#define VDC_SPRITE_HEIGHT_32    (0x1 << 12)
#define VDC_SPRITE_HEIGHT_64    (0x3 << 12)
#define VDC_SPRITE_HEIGHT_MASK  (0x3 << 12)
#define VDC_SPRITE_FLIP_X       (0x1 << 11)
#define VDC_SPRITE_FLIP_Y       (0x1 << 15)

typedef struct {
    uint16_t y;
    uint16_t x;
    uint16_t pattern;
    uint16_t attr;
} vdc_sprite_t;

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
 * @brief Set the VDC's copy method to copy every word.
 */
void pce_vdc_set_copy_word(void);
/**
 * @brief Set the VDC's copy method to copy every row.
 * Alias for @ref pce_vdc_set_copy_word .
 */
#define pce_vdc_set_copy_row() pce_vdc_set_copy_word()

/**
 * @brief Set the VDC's copy method to copy every 32nd word.
 */
void pce_vdc_set_copy_32_words(void);
/**
 * @brief Set the VDC's copy method to copy every column for a 32-wide display.
 * Alias for @ref pce_vdc_set_copy_32_words .
 */
#define pce_vdc_set_copy_column_32() pce_vdc_set_copy_32_words()

/**
 * @brief Set the VDC's copy method to copy every 64th word.
 */
void pce_vdc_set_copy_64_words(void);
/**
 * @brief Set the VDC's copy method to copy every column for a 64-wide display.
 * Alias for @ref pce_vdc_set_copy_64_words .
 */
#define pce_vdc_set_copy_column_64() pce_vdc_set_copy_64_words()

/**
 * @brief Set the VDC's copy method to copy every 128th word.
 */
void pce_vdc_set_copy_128_words(void);
/**
 * @brief Set the VDC's copy method to copy every column for a 128-wide display.
 * Alias for @ref pce_vdc_set_copy_128_words .
 */
#define pce_vdc_set_copy_column_128() pce_vdc_set_copy_128_words()

/**
 * @brief Copy data from RAM to VRAM.
 * 
 * @param dest Destination memory address, in words.
 * @param source Source memory address.
 * @param length The length, in bytes.
 */
void pce_vdc_copy_to_vram(uint16_t dest, const void *source, uint16_t length);

/**
 * @brief Copy data from VRAM to RAM.
 * 
 * @param dest Destination memory address.
 * @param source Source memory address, in words.
 * @param length The length, in bytes.
 */
void pce_vdc_copy_from_vram(void *dest, uint16_t source, uint16_t length);

/**
 * @brief Start a DMA operation on the VDC.
 * 
 * @param mode The DMA mode.
 * - @ref VDC_DMA_IRQ_SATB_DONE - IRQ on VRAM->SATB transfer completion
 * - @ref VDC_DMA_IRQ_DONE - IRQ on VRAM->VRAM transfer completion
 * - @ref VDC_DMA_SRC_DEC - decrement source pointer (increment by default)
 * - @ref VDC_DMA_DEST_DEC - decrement destination pointer (increment by default)
 * - @ref VDC_DMA_REPEAT_SATB - automatically schedule VRAM->SATB transfer
 * @param source Source address in VRAM.
 * @param dest Destination address in VRAM.
 * @param length Length, in bytes.
 */
void pce_vdc_dma_start(uint8_t mode, uint16_t source, uint16_t dest, uint16_t length);

/**
 * @brief Check if the DMA operation has finished.
 */
bool pce_vdc_dma_finished(void);

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
#define pce_vdc_set_resolution(width_pixels, height_pixels, vce_flags) \
    pce_vdc_set_width(width_pixels, vce_flags); \
    pce_vdc_set_height(height_pixels)

/**
 * @brief Set the VDC background size.
 * 
 * @param value VDC_BG_SIZE_*
 */
void pce_vdc_bg_set_size(uint8_t value);

/**
 * @brief Set the sprite attribute table location.
 * 
 * @param loc Location.
 */
 void pce_vdc_sprite_set_table_start(uint16_t loc);

/**
 * @brief Enable VDC control flags.
 * 
 * @param value Control flags.
 */
void pce_vdc_enable(uint8_t value);

/**
 * @brief Disable VDC control flags.
 * 
 * @param value Control flags.
 */
void pce_vdc_disable(uint8_t value);

/**
 * @brief Enable the background layer.
 */
#define pce_vdc_bg_enable() pce_vdc_enable(VDC_CONTROL_ENABLE_BG)

/**
 * @brief Disable the background layer.
 */
#define pce_vdc_bg_disable() pce_vdc_disable(VDC_CONTROL_ENABLE_BG)

/**
 * @brief Enable the sprite layer.
 */
#define pce_vdc_sprite_enable() pce_vdc_enable(VDC_CONTROL_ENABLE_SPRITE)

/**
 * @brief Disable the sprite layer.
 */
#define pce_vdc_sprite_disable() pce_vdc_disable(VDC_CONTROL_ENABLE_SPRITE)

/**
 * @brief Enable the scanline IRQ.
 */
#define pce_vdc_irq_scanline_enable() pce_vdc_enable(VDC_CONTROL_IRQ_SCANLINE)

/**
 * @brief Disable the scanline IRQ.
 */
#define pce_vdc_irq_scanline_disable() pce_vdc_disable(VDC_CONTROL_IRQ_SCANLINE)

/**
 * @brief Enable the sprite collision IRQ.
 */
#define pce_vdc_irq_sprite_collide_enable() pce_vdc_enable(VDC_CONTROL_IRQ_SPRITE_COLLIDE)

/**
 * @brief Disable the sprite collision IRQ.
 */
#define pce_vdc_irq_sprite_collide_disable() pce_vdc_disable(VDC_CONTROL_IRQ_SPRITE_COLLIDE)

/**
 * @brief Enable the sprite overflow IRQ.
 */
#define pce_vdc_irq_sprite_overflow_enable() pce_vdc_enable(VDC_CONTROL_IRQ_SPRITE_OVERFLOW)

/**
 * @brief Disable the sprite overflow IRQ.
 */
#define pce_vdc_irq_sprite_overflow_disable() pce_vdc_disable(VDC_CONTROL_IRQ_SPRITE_OVERFLOW)

/**
 * @brief Enable the veritcal blank IRQ.
 */
#define pce_vdc_irq_vblank_enable() pce_vdc_enable(VDC_CONTROL_IRQ_VBLANK)

/**
 * @brief Disable the veritcal blank IRQ.
 */
#define pce_vdc_irq_vblank_disable() pce_vdc_disable(VDC_CONTROL_IRQ_VBLANK)

/**
 * @brief SuperGrafx: Initialize the second VDC.
 * 
 * This function *must* be called if you plan on using pce_sgx_vdc* methods.
 */
void pce_sgx_vdc_init(void);

/**
 * @brief SuperGrafx: Set the VDC1 as the current VDC for pce_vdc functions.
 */
void pce_sgx_vdc1_set(void);

/**
 * @brief SuperGrafx: Set the VDC2 as the current VDC for pce_vdc functions.
 */
void pce_sgx_vdc2_set(void);

/**
 * @brief SuperGrafx: Set the specified VDC as the current VDC for pce_vdc functions.
 */
void pce_sgx_vdc_set(uint8_t id);

/**
 * @brief SuperGrafx: Get the current VDC's index port location.
 */
volatile uint8_t *pce_sgx_vdc_get_index();

/**
 * @brief SuperGrafx: Get the current VDC's data port location.
 */
volatile uint16_t *pce_sgx_vdc_get_data();

#ifdef __cplusplus
}
#endif

#endif /* _PCE_VDC_H_ */