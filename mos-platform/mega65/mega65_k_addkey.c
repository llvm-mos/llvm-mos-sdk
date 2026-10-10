// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Add a PETSCII character to the keyboard input buffer (ADDKEY, $FF4A).
/// @return 0 on success, 1 if the buffer is full.
uint8_t mega65_k_addkey(unsigned char petscii_char) {
  uint8_t full;
  // ADDKEY answers in the carry, which has to be consumed here: "=c" outputs
  // miscompile (see mega65_k_load.c).
  asm volatile("jsr __ADDKEY\n"
               "lda #0\n"
               "bcc 1f\n"
               "lda #1\n"
               "1:\n"
               : "=a"(full)
               : "a"(petscii_char)
               : "x", "y", "p");
  return full;
}
