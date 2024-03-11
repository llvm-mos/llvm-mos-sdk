// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

__attribute__((section(".zp.pal_update"))) volatile char PAL_UPDATE;
__attribute__((weak, aligned(32), section(".aligned.pal_buf"))) volatile char PAL_BUF[32];

void pal_col(char index, char color) {
  PAL_BUF[index & 0x1f] = color;
  ++PAL_UPDATE;
}
