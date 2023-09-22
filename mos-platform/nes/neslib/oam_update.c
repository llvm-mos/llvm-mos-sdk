// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

__attribute__((section(".zp.sprid"))) unsigned SPRID;

void oam_set(char index) { SPRID = index & 0xfc; }

char oam_get(void) { return SPRID; }
