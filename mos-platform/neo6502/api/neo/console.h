// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_CONSOLE_H
#define _NEO_CONSOLE_H

#include <neo6502.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read and remove a key press.
 *
 * @return ASCII key value; 0 if no key presses queued.
 */
char neo_console_read_char(void);

/**
 * @brief Check to see if the keyboard queue is empty.
 *
 * @return 0xFF if the queue is empty, 0 otherwise.
 */
uint8_t neo_console_status(void);

/**
 * @brief Read the current line below the cursor, and move the cursor by one line. The line is stored in Pascal string format.
 *
 * Multi-line input is supported.
 *
 * @param line Buffer for the line to be read.
 */
void neo_console_read_line_p(neo_pstring_t *line);

/**
 * @brief Read the current line below the cursor, and move the cursor by one line. The line is stored in C string format.
 *
 * Multi-line input is supported.
 *
 * @param line Buffer for the line to be read.
 */
void neo_console_read_line(char *line);

/**
 * @brief Define a hotkey which emits a Pascal-style string when pressed.
 *
 * @param hotkey Function key to act as a hotkey (F1-F10 => 1-10)
 * @param str String to emit when pressed.
 */
void neo_console_define_hotkey_p(uint8_t hotkey, const neo_pstring_t *str);

/**
 * @brief Define a hotkey which emits a C-style string when pressed.
 *
 * @param hotkey Function key to act as a hotkey (F1-F10 => 1-10)
 * @param str String to emit when pressed.
 */
void neo_console_define_hotkey(uint8_t hotkey, const char *str);

/**
 * @brief Define a font character.
 *
 * @param ch Character (192-255)
 * @param bitmap 7-byte (bits 0..5 => 6x7) character bitmap.
 */
void neo_console_define_char(char ch, const uint8_t *bitmap);

/**
 * @brief Write a character to the console.
 *
 * @param ch Character
 */
void neo_console_write_char(char ch);

/**
 * @brief Move the cursor to the specified position.
 *
 * @param x X
 * @param y Y
 */
void neo_console_set_cursor_pos(uint8_t x, uint8_t y);

/**
 * @brief Display the current function key definitions.
 */
void neo_console_list_hotkeys(void);

/**
 * @brief Fetch the console size, in characters.
 *
 * @param width Width
 * @param height Height
 */
void neo_console_screen_size(uint8_t *width, uint8_t *height);

/**
 * @brief Clear the console screen.
 */
void neo_console_clear_screen(void);

/**
 * @brief Fetch the cursor position.
 *
 * @param x X
 * @param y Y
 */
void neo_console_cursor_pos(uint8_t *x, uint8_t *y);

/**
 * @brief Clear all characters within the specified region.
 *
 * @param x1 Begin X
 * @param y1 Begin Y
 * @param x2 End X
 * @param y2 End Y
 */
void neo_console_clear_region(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

/**
 * @brief Set the text color.
 *
 * @param fg Foreground color.
 * @param bg Background color.
 */
void neo_console_set_text_color(uint8_t fg, uint8_t bg);

/**
 * @brief Fetch the text color.
 *
 * @param fg Foreground color.
 * @param bg Background color.
 */
void neo_console_get_text_color(uint8_t *fg, uint8_t *bg);

/**
 * @brief Set the cursor visibility.
 */
void neo_console_set_cursor_visibility(uint8_t value);

#ifdef __cplusplus
}
#endif

#endif
