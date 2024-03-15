// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "../neo6502.h"
#include "../kernel.h"

void neo_sound_reset(void) {
    KSendMessage(API_GROUP_SOUND, API_FN_RESET_SOUND);
}

void neo_sound_reset_channel(uint8_t channel) {
    ControlPort.params[0] = channel;
    KSendMessage(API_GROUP_SOUND, API_FN_RESET_CHANNEL);
}

void neo_sound_beep(void) {
    KSendMessage(API_GROUP_SOUND, API_FN_BEEP);
}

void neo_sound_queue(uint8_t channel, uint16_t frequency, uint16_t duration, uint16_t slide, uint8_t target) {
    ControlPort.params[0] = channel;
    *((volatile uint16_t*) (ControlPort.params + 1)) = frequency;
    *((volatile uint16_t*) (ControlPort.params + 3)) = duration;
    *((volatile uint16_t*) (ControlPort.params + 5)) = slide;
    ControlPort.params[7] = target;
    KSendMessage(API_GROUP_SOUND, API_FN_QUEUE_SOUND);
}

void neo_sound_play_effect(uint8_t channel, uint8_t id) {
    ControlPort.params[0] = channel;
    ControlPort.params[1] = id;
    KSendMessage(API_GROUP_SOUND, API_FN_PLAY_SOUND);
}

uint8_t neo_sound_status(uint8_t channel) {
    ControlPort.params[0] = channel;
    KSendMessageSync(API_GROUP_SOUND, API_FN_SOUND_STATUS);
    return ControlPort.params[0];
}
