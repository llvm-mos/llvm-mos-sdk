// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "../neo6502.h"
#include "../kernel.h"

uint8_t neo_controller_read(void) {
    KSendMessageSync(API_GROUP_CONTROLLER, API_FN_READ_CONTROLLER);
    return ControlPort.params[0];
}
