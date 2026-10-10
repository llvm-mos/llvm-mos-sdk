// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D640: d81write_en ($44).

#include <mega65.h>

mega65_h_err mega65_h_d81write_en(void) {
  uint8_t err;
  asm volatile("lda #$44\n"
               "sta $d640\n"
               "clv\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err)
               :
               : "x", "y", "p");
  return err;
}
