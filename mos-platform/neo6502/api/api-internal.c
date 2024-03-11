// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>
#include <string.h>
#include "api-internal.h"

void __neo_depascalize_output(char *to) {
    uint8_t to_len = to[0];
    memmove(to, to + 1, to_len);
    to[to_len] = 0;
}
