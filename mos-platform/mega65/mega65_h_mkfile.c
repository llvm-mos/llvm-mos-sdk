// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D640: mkfile ($1E).

#include <mega65.h>

mega65_h_err mega65_h_mkfile(uint32_t size) {
  uint8_t size_lo = (uint8_t)size;
  uint8_t size_mid = (uint8_t)(size >> 8);
  uint8_t size_hi = (uint8_t)(size >> 16);
  uint8_t err;
  // The size travels in X/Y/Z, so Z has to be restored to 0 before returning
  // to compiled code.
  asm volatile("ldz %[hi]\n"
               "lda #$1e\n"
               "sta $d640\n"
               "clv\n"
               "ldz #0\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+x"(size_lo), "+y"(size_mid)
               : [hi] "r"(size_hi)
               : "p");
  return err;
}
