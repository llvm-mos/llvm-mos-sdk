// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Enable or disable KERNAL messages (SETMSG, $FF90).
/// Bit 7 = control messages, bit 6 = error messages.
void mega65_k_setmsg(uint8_t mode) {
  asm volatile("jsr __SETMSG" : : "a"(mode) : "x", "y", "p");
}
