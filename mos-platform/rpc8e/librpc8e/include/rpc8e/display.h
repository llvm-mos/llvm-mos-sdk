/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _RPC8E_DISPLAY_H_
#define _RPC8E_DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file display.h
 * Functionality related to the display.
 */

#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 50

/**
 * @brief Copy an area of the display to another location.
 *
 * @param sx Source X position.
 * @param sy Source Y position.
 * @param dx Destination X position.
 * @param dy Destination Y position.
 * @param width Width.
 * @param height Height.
 */
void rpc8e_display_blit_shift(uint8_t sx, uint8_t sy, uint8_t dx, uint8_t dy, uint8_t width, uint8_t height);

/**
 * @brief Fill an area of the display with a character.
 *
 * @param x Destination X position.
 * @param y Destination Y position.
 * @param width Width.
 * @param height Height.
 * @param fiilchar The character to fill the area with.
 */
void rpc8e_display_blit_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t fillchar);

/**
 * @brief Clear the display.
 */
void rpc8e_display_clear(void);

/**
 * @brief Return the cursor's current X position.
 */
uint8_t rpc8e_display_wherex(void);

/**
 * @brief Return the cursor's current Y position.
 */
uint8_t rpc8e_display_wherey(void);

/**
 * @brief Enable or disable "reverse video" mode.
 */
void rpc8e_display_revers(bool value);

/**
 * @brief Move the cursor to a specific X position.
 *
 * @param x X position.
 */
void rpc8e_display_gotox(uint8_t x);

/**
 * @brief Move the cursor to a specific Y position.
 *
 * @param y Y position.
 */
void rpc8e_display_gotoy(uint8_t y);

/**
 * @brief Move the cursor to a specific X/Y position.
 *
 * @param x X position.
 * @param y Y position.
 */
void rpc8e_display_gotoxy(uint8_t x, uint8_t y);

/**
 * @brief Put a character on the display.
 *
 * @param x X position.
 * @param y Y position.
 * @param value The character to put.
 */
void rpc8e_display_put(uint8_t x, uint8_t y, uint8_t value);

/**
 * @brief Return true if a key has been pressed and is awaiting in the queue.
 */
bool rpc8e_display_key_pressed(void);

/**
 * @brief Return a key from the queue.
 *
 * @return int A key from the queue, or -1 if the queue is empty.
 */
int rpc8e_display_key_read(void);

#ifdef __cplusplus
}
#endif

#endif /* _RPC8E_DISPLAY_H_ */
