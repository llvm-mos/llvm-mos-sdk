// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Search for a logical file number in use (LKUPLA, $FF5F).
/// @return 0 if found (writes device and SA to output params), 1 if not found.
uint8_t mega65_k_lkupla(uint8_t la, uint8_t *fa, uint8_t *sa) {
  uint8_t x, y, missing;
  // The answer is in the carry, which has to be consumed here: "=c" outputs
  // miscompile (see mega65_k_load.c).
  asm volatile("jsr __LKUPLA\n"
               "lda #0\n"
               "bcc 1f\n"
               "lda #1\n"
               "1:\n"
               : "=a"(missing), "=x"(x), "=y"(y)
               : "a"(la)
               : "p");
  if (missing)
    return 1;
  *fa = x;
  *sa = y;
  return 0;
}
