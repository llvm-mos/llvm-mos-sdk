// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "../neo6502.h"
#include "../kernel.h"

void neo_turtle_init(uint8_t idx) {
    ControlPort.params[0] = idx;
    KSendMessage(API_GROUP_TURTLE, API_FN_TURTLE_INIT);
}

void neo_turtle_turn(int16_t deg) {
    *((volatile uint16_t*) (ControlPort.params + 0)) = deg;
    KSendMessage(API_GROUP_TURTLE, API_FN_TURTLE_TURN);
}

void neo_turtle_move(int16_t len, uint8_t color, uint8_t pen) {
    *((volatile uint16_t*) (ControlPort.params + 0)) = len;
    ControlPort.params[2] = color;
    ControlPort.params[3] = pen;
    KSendMessage(API_GROUP_TURTLE, API_FN_TURTLE_MOVE);
}

void neo_turtle_hide(void) {
    KSendMessage(API_GROUP_TURTLE, API_FN_TURTLE_HIDE);
}

void neo_turtle_home(void) {
    KSendMessage(API_GROUP_TURTLE, API_FN_TURTLE_HOME);
}
