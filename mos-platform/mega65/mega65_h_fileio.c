// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// readfile/writefile operate on the "current file" set by openfile.
// Data is transferred via the Hyppo sector buffer at $FFD6E00-$FFD6FFF.
//
// Trap $D640: openfile ($18), readfile ($1A), closefile ($20),
// closeall ($22), rmfile ($26).
//
// Success is C=1, error code in A. The carry is consumed inside each asm
// block; see mega65_k_load.c for why an "=c" output cannot be used.

#include <mega65.h>

mega65_h_err mega65_h_openfile(uint8_t *fd) {
  uint8_t result, ok;
  asm volatile("lda #$18\n"
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

mega65_h_err mega65_h_readfile(uint16_t *count) {
  uint8_t err, lo, hi, ok;
  // End of file is reported as a failure with A=0 and a zero byte count, so
  // the count must be written on both paths for the caller's 0-means-EOF
  // test to work. A already holds the error code, so the carry is turned into
  // a value around it rather than in it.
  asm volatile("lda #$1a\n"
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

void mega65_h_closefile(uint8_t fd) {
  asm volatile("lda #$20\n"
               "sta $d640\n"
               "clv\n"
               : "+x"(fd)
               :
               : "a", "y", "p");
}

void mega65_h_closeall(void) {
  asm volatile("lda #$22\n"
               "sta $d640\n"
               "clv\n"
               :
               :
               : "a", "x", "y", "p");
}

mega65_h_err mega65_h_rmfile(void) {
  uint8_t err;
  asm volatile("lda #$26\n"
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
