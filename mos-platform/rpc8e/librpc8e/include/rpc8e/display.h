/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once
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

void rpc8e_display_blit_shift(uint8_t sx, uint8_t sy, uint8_t dx, uint8_t dy, uint8_t width, uint8_t height);
void rpc8e_display_blit_fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t fillchar);
void rpc8e_display_clear(void);
uint8_t rpc8e_display_wherex(void);
uint8_t rpc8e_display_wherey(void);
void rpc8e_display_revers(bool value);
void rpc8e_display_gotox(uint8_t x);
void rpc8e_display_gotoy(uint8_t y);
void rpc8e_display_gotoxy(uint8_t x, uint8_t y);
void rpc8e_display_put(uint8_t x, uint8_t y, uint8_t value);
bool rpc8e_display_key_pressed(void);
int rpc8e_display_key_read(void);

#ifdef __cplusplus
}
#endif
