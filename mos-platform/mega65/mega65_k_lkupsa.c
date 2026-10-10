// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Search for a secondary address in use (LKUPSA, $FF62).
/// @return 0 if found (writes LA and device to output params), 1 if not found.
uint8_t mega65_k_lkupsa(uint8_t sa, uint8_t *la, uint8_t *fa) {
  uint8_t a, x, missing;
  // A holds the logical file number on return, so the carry is parked in an
  // imaginary register rather than in A. "=c" outputs miscompile (see
  // mega65_k_load.c).
  asm volatile("jsr __LKUPSA\n"
               "pha\n"
               "lda #0\n"
               "bcc 1f\n"
               "lda #1\n"
               "1:\n"
               "sta %[missing]\n"
               "pla\n"
               : "=a"(a), "=x"(x), [missing] "=&r"(missing), "+y"(sa)
               :
               : "p");
  if (missing)
    return 1;
  *la = a;
  *fa = x;
  return 0;
}
