// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdbool.h>
#include "../neo6502.h"
#include "../kernel.h"

__attribute__((leaf))
void neo_sprite_reset(void) {
    KSendMessage(API_GROUP_SPRITES, API_FN_SPRITE_RESET);
}

__attribute__((leaf))
void neo_sprite_set(uint8_t id, uint16_t x, uint16_t y, uint8_t img, uint8_t flip, uint8_t anchor) {
    ControlPort.params[0] = id;
    *((volatile uint16_t*) (ControlPort.params + 1)) = x;
    *((volatile uint16_t*) (ControlPort.params + 3)) = y;
    ControlPort.params[5] = img;
    ControlPort.params[6] = flip;
    ControlPort.params[7] = anchor;
    KSendMessage(API_GROUP_SPRITES, API_FN_SPRITE_SET);
}

__attribute__((leaf))
void neo_sprite_hide(uint8_t id) {
    ControlPort.params[0] = id;
    KSendMessage(API_GROUP_SPRITES, API_FN_SPRITE_HIDE);
}

__attribute__((leaf))
bool neo_sprite_collision(uint8_t first, uint8_t second, uint8_t distance) {
    ControlPort.params[0] = first;
    ControlPort.params[1] = second;
    ControlPort.params[2] = distance;
    KSendMessageSync(API_GROUP_SPRITES, API_FN_SPRITE_COLLISION);
    return ControlPort.params[0];
}

__attribute__((leaf))
void neo_sprite_position(uint8_t id, uint16_t *x, uint16_t *y) {
    ControlPort.params[0] = id;
    KSendMessageSync(API_GROUP_SPRITES, API_FN_SPRITE_POS);
    if (x) *x = *((volatile uint16_t*) (ControlPort.params + 1));
    if (y) *y = *((volatile uint16_t*) (ControlPort.params + 3));
}

