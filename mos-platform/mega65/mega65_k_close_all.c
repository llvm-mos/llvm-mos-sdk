// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Close all open files on the specified device (CLOSE_ALL, $FF50).
/// Restores default I/O channels if the current channel was on that device.
void mega65_k_close_all(uint8_t device) {
  // CLOSE_ALL reloads A from its own state before returning, so the device
  // number does not survive the call.
  asm volatile("jsr __CLOSE_ALL" : "+a"(device) : : "x", "y", "p");
}
