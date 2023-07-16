/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 *
 * Portions originally from the rpc8e-cc65 project:
 * https://github.com/steventroughtonsmith/rpc8e-cc65/blob/master/rpc8e/conio.c
 * Modified for LLVM-MOS SDK.
 *
 * Copyright (C) 2012 L. Adamson
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */

#include <rpc8e.h>
#include <stdint.h>

static bool reverse_video = 0;

void rpc8e_display_blit_shift(uint8_t sx, uint8_t sy, uint8_t dx, uint8_t dy,
                              uint8_t width, uint8_t height) {
  *IO_DISPLAY_BLIT_SRC_X = sx;
  *IO_DISPLAY_BLIT_SRC_Y = sy;
  *IO_DISPLAY_BLIT_DEST_X = dx;
  *IO_DISPLAY_BLIT_DEST_Y = dy;
  *IO_DISPLAY_BLIT_WIDTH = width;
  *IO_DISPLAY_BLIT_HEIGHT = height;

  *IO_DISPLAY_BLIT_MODE = DISPLAY_BLIT_MODE_SHIFT;
  while (*IO_DISPLAY_BLIT_MODE == DISPLAY_BLIT_MODE_SHIFT) {
    rpc8e_cpu_wait();
  }
}

void rpc8e_display_blit_fill(uint8_t x, uint8_t y, uint8_t width,
                             uint8_t height, uint8_t fillchar) {
  *IO_DISPLAY_BLIT_FILL_VALUE = fillchar;
  *IO_DISPLAY_BLIT_DEST_X = x;
  *IO_DISPLAY_BLIT_DEST_Y = y;
  *IO_DISPLAY_BLIT_WIDTH = width;
  *IO_DISPLAY_BLIT_HEIGHT = height;

  *IO_DISPLAY_BLIT_MODE = DISPLAY_BLIT_MODE_FILL;
  while (*IO_DISPLAY_BLIT_MODE == DISPLAY_BLIT_MODE_FILL) {
    rpc8e_cpu_wait();
  }
}

void rpc8e_display_clear(void) {
  rpc8e_display_blit_fill(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, ' ');
  *IO_DISPLAY_ROW_Y = 0;
  *IO_DISPLAY_CURSOR_X = 0;
  *IO_DISPLAY_CURSOR_Y = 0;
}

uint8_t rpc8e_display_wherex(void) { return *IO_DISPLAY_CURSOR_X; }

uint8_t rpc8e_display_wherey(void) { return *IO_DISPLAY_CURSOR_Y; }

void rpc8e_display_revers(bool value) { reverse_video = value; }

void rpc8e_display_gotox(uint8_t x) { *IO_DISPLAY_CURSOR_X = x; }

void rpc8e_display_gotoy(uint8_t y) {
  *IO_DISPLAY_ROW_Y = y;
  *IO_DISPLAY_CURSOR_Y = y;
}

void rpc8e_display_gotoxy(uint8_t x, uint8_t y) {
  *IO_DISPLAY_ROW_Y = y;
  *IO_DISPLAY_CURSOR_X = x;
  *IO_DISPLAY_CURSOR_Y = y;
}

void rpc8e_display_put(uint8_t x, uint8_t y, uint8_t value) {
  uint8_t old_y = *IO_DISPLAY_ROW;
  *IO_DISPLAY_ROW_Y = y;
  IO_DISPLAY_ROW[x] = value;
  *IO_DISPLAY_ROW_Y = old_y;
}

bool rpc8e_display_key_pressed(void) {
  return *IO_DISPLAY_KEY_BUFFER_START == *IO_DISPLAY_KEY_BUFFER_POS;
}

int rpc8e_display_key_read(void) {
  if (!rpc8e_display_key_pressed()) {
    return -1;
  }

  uint8_t key = *IO_DISPLAY_KEY_BUFFER_VALUE;
  *IO_DISPLAY_KEY_BUFFER_START = (*IO_DISPLAY_KEY_BUFFER_START + 1) & 0x0F;
  return key;
}

int getchar(void) {
  uint8_t old_device = rpc8e_redbus_map(boot_display_id);

  while (!rpc8e_display_key_pressed()) {
    rpc8e_cpu_wait();
  }

  uint8_t key = *IO_DISPLAY_KEY_BUFFER_VALUE;
  *IO_DISPLAY_KEY_BUFFER_START = (*IO_DISPLAY_KEY_BUFFER_START + 1) & 0x0F;

  rpc8e_redbus_set_map(old_device);

  return key;
}

void __putchar(char c) {
  uint8_t x, y, i;

  uint8_t old_device = rpc8e_redbus_map(boot_display_id);

  // Set or unset reverse video bit, if needed.
  if (reverse_video) {
    c ^= 0x80;
  }

  // Read the current cursor position.
  x = *IO_DISPLAY_CURSOR_X;
  y = *IO_DISPLAY_CURSOR_Y;

  // Set the display memory window to the line the cursor is on.
  *IO_DISPLAY_ROW_Y = y;

  // Write the character the the column the cursor is in, within the display
  // memory window.
  if (c != '\n') {
    IO_DISPLAY_ROW[x] = c;
  }

  // Advance the cursor.
  ++x;
  if (x >= DISPLAY_WIDTH || c == '\n') {
    x = 0;
    if (y >= (DISPLAY_HEIGHT - 1)) {
      // Scroll and clear last line.
      rpc8e_display_blit_shift(0, 1, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT - 1);

      for (i = 0; i < DISPLAY_WIDTH; i++) {
        IO_DISPLAY_ROW[i] = ' ';
      }
    } else {
      // Advance line.
      ++y;
      *IO_DISPLAY_CURSOR_Y = y;
      *IO_DISPLAY_ROW_Y = y;
    }
  }

  // Set the cursor to the new position.
  *IO_DISPLAY_CURSOR_X = x;

  rpc8e_redbus_set_map(old_device);
}
