// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <string.h>
#include "../neo6502.h"
#include "../kernel.h"
#include "api-internal.h"

void neo_graphics_set_defaults(uint8_t color_mask, uint8_t color_xor, uint8_t fill, uint8_t extent, uint8_t flip) {
    ControlPort.params[0] = color_mask;
    ControlPort.params[1] = color_xor;
    ControlPort.params[2] = fill;
    ControlPort.params[3] = extent;
    ControlPort.params[4] = flip;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_GFX);
}

void neo_graphics_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    ((volatile uint16_t*) ControlPort.params)[0] = x1;
    ((volatile uint16_t*) ControlPort.params)[1] = y1;
    ((volatile uint16_t*) ControlPort.params)[2] = x2;
    ((volatile uint16_t*) ControlPort.params)[3] = y2;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_LINE);
}

void neo_graphics_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    ((volatile uint16_t*) ControlPort.params)[0] = x1;
    ((volatile uint16_t*) ControlPort.params)[1] = y1;
    ((volatile uint16_t*) ControlPort.params)[2] = x2;
    ((volatile uint16_t*) ControlPort.params)[3] = y2;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_RECT);
}

void neo_graphics_draw_ellipse(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    ((volatile uint16_t*) ControlPort.params)[0] = x1;
    ((volatile uint16_t*) ControlPort.params)[1] = y1;
    ((volatile uint16_t*) ControlPort.params)[2] = x2;
    ((volatile uint16_t*) ControlPort.params)[3] = y2;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_ELLIPSE);
}

void neo_graphics_draw_pixel(uint16_t x, uint16_t y) {
    ((volatile uint16_t*) ControlPort.params)[0] = x;
    ((volatile uint16_t*) ControlPort.params)[1] = y;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_PIXEL);
}

void neo_graphics_draw_text_p(uint16_t x, uint16_t y, const neo_pstring_t *text) {
    ((volatile uint16_t*) ControlPort.params)[0] = x;
    ((volatile uint16_t*) ControlPort.params)[1] = y;
    ((volatile uint16_t*) ControlPort.params)[2] = (uint16_t) text;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_TEXT);
}

void neo_graphics_draw_text(uint16_t x, uint16_t y, const char *text) {
    PASCALIZE_INPUT(text, text_p);
    neo_graphics_draw_text_p(x, y, (const neo_pstring_t *) text_p);
}

void neo_graphics_draw_image(uint16_t x, uint16_t y, uint8_t id) {
    ((volatile uint16_t*) ControlPort.params)[0] = x;
    ((volatile uint16_t*) ControlPort.params)[1] = y;
    ControlPort.params[4] = id;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_IMG);
}

void neo_graphics_draw_tilemap(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    ((volatile uint16_t*) ControlPort.params)[0] = x1;
    ((volatile uint16_t*) ControlPort.params)[1] = y1;
    ((volatile uint16_t*) ControlPort.params)[2] = x2;
    ((volatile uint16_t*) ControlPort.params)[3] = y2;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_DRAW_TILEMAP);
}

void neo_graphics_set_palette(uint8_t idx, uint8_t r, uint8_t g, uint8_t b) {
    ControlPort.params[0] = idx;
    ControlPort.params[1] = r;
    ControlPort.params[2] = g;
    ControlPort.params[3] = b;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_PALETTE);
}

uint8_t neo_graphics_read_pixel(uint16_t x, uint16_t y) {
    ((volatile uint16_t*) ControlPort.params)[0] = x;
    ((volatile uint16_t*) ControlPort.params)[1] = y;
    KSendMessageSync(API_GROUP_GRAPHICS, API_FN_READ_PIXEL);
    return ControlPort.params[0];
}

void neo_graphics_write_pixel(uint16_t x, uint16_t y, uint8_t idx) {
    ((volatile uint16_t*) ControlPort.params)[0] = x;
    ((volatile uint16_t*) ControlPort.params)[1] = y;
    ControlPort.params[4] = idx;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_WRITE_PIXEL);
}

void neo_graphics_reset_palette(void) {
    KSendMessage(API_GROUP_GRAPHICS, API_FN_RESET_PALETTE);
}

void neo_graphics_set_tilemap(const void *src, uint16_t x, uint16_t y) {
    ((volatile uint16_t*) ControlPort.params)[0] = (uint16_t) src;
    ((volatile uint16_t*) ControlPort.params)[1] = x;
    ((volatile uint16_t*) ControlPort.params)[2] = y;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_TILEMAP);
}

long neo_graphics_frame_count(void) {
    KSendMessageSync(API_GROUP_GRAPHICS, API_FN_FRAME_COUNT);
    return *((long*) ControlPort.params);
}

void neo_graphics_set_color(uint8_t idx) {
    ControlPort.params[0] = idx;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_COLOR);
}

void neo_graphics_set_solid_flag(uint8_t value) {
    ControlPort.params[0] = value;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_SOLID);
}

void neo_graphics_set_draw_size(uint8_t value) {
    ControlPort.params[0] = value;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_DRAW_SIZE);
}

void neo_graphics_set_flip_bits(uint8_t value) {
    ControlPort.params[0] = value;
    KSendMessage(API_GROUP_GRAPHICS, API_FN_SET_FLIP);
}

