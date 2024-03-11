// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "../neo6502.h"
#include "../kernel.h"

__attribute__((leaf))
uint8_t neo_api_error(void) {
    KWaitMessage();
    return ControlPort.error;
}

__attribute__((leaf))
long neo_system_timer(void) {
	KSendMessageSync(API_GROUP_SYSTEM, API_FN_TIMER);
	return *((long*) ControlPort.params);
}

__attribute__((leaf))
uint8_t neo_system_key_status(char key) {
    ControlPort.params[0] = key;
	KSendMessageSync(API_GROUP_SYSTEM, API_FN_KEY_STATUS);
	return ControlPort.params[0];
}

__attribute__((leaf))
void neo_system_credits(void) {
    KSendMessage(API_GROUP_SYSTEM, API_FN_CREDITS);
}

__attribute__((leaf))
void neo_system_serial_update(void) {
    KSendMessage(API_GROUP_SYSTEM, API_FN_SERIAL_STATUS);
}

__attribute__((leaf))
void neo_system_locale(const char *locale) {
    ControlPort.params[0] = locale[0];
    ControlPort.params[1] = locale[1];
    KSendMessage(API_GROUP_SYSTEM, API_FN_LOCALE);
}

__attribute__((leaf))
void neo_system_reset(void) {
    KSendMessage(API_GROUP_SYSTEM, API_FN_RESET);
}
