// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D640: opendir ($12), readdir ($14), closedir ($16),
// chdir ($0C), cdrootdir ($3C).
//
// Success is C=1, error code in A. The carry is consumed inside each asm
// block; see mega65_k_load.c for why an "=c" output cannot be used.

#include <mega65.h>

mega65_h_err mega65_h_opendir(uint8_t *fd) {
  uint8_t result, ok;
  asm volatile("lda #$12\n"
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

mega65_h_err mega65_h_readdir(uint8_t fd, mega65_h_dirent *dest) {
  uint8_t page = (uint16_t)dest >> 8;
  uint8_t err;
  asm volatile("lda #$14\n"
               "sta $d640\n"
               "clv\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+x"(fd), "+y"(page)
               :
               : "p");
  return err;
}

void mega65_h_closedir(uint8_t fd) {
  asm volatile("lda #$16\n"
               "sta $d640\n"
               "clv\n"
               : "+x"(fd)
               :
               : "a", "y", "p");
}

mega65_h_err mega65_h_chdir(void) {
  uint8_t err;
  asm volatile("lda #$0c\n"
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

mega65_h_err mega65_h_cdrootdir(uint8_t drive) {
  uint8_t err;
  asm volatile("lda #$3c\n"
               "sta $d640\n"
               "clv\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+x"(drive)
               :
               : "y", "p");
  return err;
}
