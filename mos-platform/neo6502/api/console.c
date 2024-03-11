// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <string.h>
#include "../neo6502.h"
#include "../kernel.h"

__attribute__((leaf))
char neo_console_read_char(void) {
    KSendMessageSync(API_GROUP_CONSOLE, API_FN_READ_CHAR);
    return ControlPort.params[0];
}

__attribute__((leaf))
uint8_t neo_console_status(void) {
    KSendMessageSync(API_GROUP_CONSOLE, API_FN_CONSOLE_STATUS);
    return ControlPort.params[0];
}

// FIXME: neo_console_read_line
// FIXME: neo_console_define_hotkey

__attribute__((leaf))
void neo_console_define_char(char ch, const uint8_t *bitmap) {
    ControlPort.params[0] = ch;
    memcpy((void*) ControlPort.params + 1, bitmap, 7);
    KSendMessage(API_GROUP_CONSOLE, API_FN_DEFINE_CHAR);
}

__attribute__((leaf))
void neo_console_write_char(char ch) {
    ControlPort.params[0] = ch;
    KSendMessage(API_GROUP_CONSOLE, API_FN_WRITE_CHAR);
}

__attribute__((leaf))
void neo_console_set_cursor_pos(uint8_t x, uint8_t y) {
    ControlPort.params[0] = x;
    ControlPort.params[1] = y;
    KSendMessage(API_GROUP_CONSOLE, API_FN_SET_CURSOR_POS);
}

__attribute__((leaf))
void neo_console_list_hotkeys(void) {
    KSendMessage(API_GROUP_CONSOLE, API_FN_LIST_HOTKEYS);
}

__attribute__((leaf))
void neo_console_screen_size(uint8_t *width, uint8_t *height) {
    KSendMessageSync(API_GROUP_CONSOLE, API_FN_SCREEN_SIZE);
    if (width) *width = ControlPort.params[0];
    if (height) *height = ControlPort.params[1];
}

__attribute__((leaf))
void neo_console_clear_screen(void) {
    KSendMessage(API_GROUP_CONSOLE, API_FN_CLEAR_SCREEN);
}

__attribute__((leaf))
void neo_console_cursor_pos(uint8_t *x, uint8_t *y) {
    KSendMessageSync(API_GROUP_CONSOLE, API_FN_CURSOR_POS);
    if (x) *x = ControlPort.params[0];
    if (y) *y = ControlPort.params[1];
}

__attribute__((leaf))
void neo_console_clear_region(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    ControlPort.params[0] = x1;
    ControlPort.params[1] = y1;
    ControlPort.params[2] = x2;
    ControlPort.params[3] = y2;
    KSendMessage(API_GROUP_CONSOLE, API_FN_CLEAR_REGIION);
}

__attribute__((leaf))
void neo_console_set_text_color(uint8_t fg, uint8_t bg) {
    ControlPort.params[0] = fg;
    ControlPort.params[1] = bg;
    KSendMessage(API_GROUP_CONSOLE, API_FN_SET_TEXT_COLOR);
}
