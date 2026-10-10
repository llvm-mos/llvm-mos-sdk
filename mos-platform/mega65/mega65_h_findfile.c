// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D640: findfile ($34), findfirst ($30), findnext ($32).
// All require mega65_h_setname() to be called first.
//
// Success is C=1, error code in A. The carry is consumed inside each asm
// block; see mega65_k_load.c for why an "=c" output cannot be used.

#include <mega65.h>

mega65_h_err mega65_h_findfile(void) {
  uint8_t err;
  asm volatile("lda #$34\n"
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

mega65_h_err mega65_h_findfirst(uint8_t *fd) {
  uint8_t result, ok;
  asm volatile("lda #$30\n"
               "sta $d640\n"
               "clv\n"
               "ldx #0\n"
               "bcc 1f\n"
               "inx\n"
               "1:\n"
               : "=a"(result), "=x"(ok)
               :
               : "y", "p");
  if (!ok)
    return result;
  *fd = result;
  return 0;
}

mega65_h_err mega65_h_findnext(void) {
  uint8_t err;
  asm volatile("lda #$32\n"
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
