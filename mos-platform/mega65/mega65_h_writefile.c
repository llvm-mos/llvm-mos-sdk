// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D640: writefile ($1C).

#include <mega65.h>

mega65_h_err mega65_h_writefile(uint16_t *count) {
  uint8_t err, lo, hi, ok;
  // The count must be written on both paths, as in mega65_h_readfile: a caller
  // looping until it reaches zero would otherwise read a stale value.
  asm volatile("lda #$1c\n"
               "sta $d640\n"
               "clv\n"
               "pha\n"
               "lda #0\n"
               "bcc 1f\n"
               "lda #1\n"
               "1:\n"
               "sta %[ok]\n"
               "pla\n"
               : "=a"(err), "=x"(lo), "=y"(hi), [ok] "=&r"(ok)
               :
               : "p");
  if (!ok) {
    *count = 0;
    return err;
  }
  *count = ((uint16_t)hi << 8) | lo;
  return 0;
}
