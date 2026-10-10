// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Bypasses KERNAL entirely. Operates on the SD card FAT filesystem,
// not D81 disk images. No MAP state interaction: safe for use with banking.
//
// Trap $D640: loadfile ($36), loadfile_attic ($3E).
//
// Success is C=1, error code in A. The carry is consumed inside each asm
// block; see mega65_k_load.c for why an "=c" output cannot be used.
//
// The destination address is passed in X/Y/Z, so Z has to be restored to 0
// before returning to compiled code.

#include <mega65.h>

mega65_h_err mega65_h_loadfile(uint32_t addr) {
  uint8_t addr_lo = (uint8_t)(addr);
  uint8_t addr_mid = (uint8_t)(addr >> 8);
  uint8_t addr_hi = (uint8_t)(addr >> 16);
  uint8_t err;

  asm volatile("ldz %[hi]\n"
               "lda #$36\n"
               "sta $d640\n"
               "clv\n"
               "ldz #0\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+x"(addr_lo), "+y"(addr_mid)
               : [hi] "r"(addr_hi)
               : "p");
  return err;
}

mega65_h_err mega65_h_loadfile_attic(uint32_t addr) {
  uint8_t addr_lo = (uint8_t)(addr);
  uint8_t addr_mid = (uint8_t)(addr >> 8);
  uint8_t addr_hi = (uint8_t)(addr >> 16);
  uint8_t err;

  asm volatile("ldz %[hi]\n"
               "lda #$3e\n"
               "sta $d640\n"
               "clv\n"
               "ldz #0\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+x"(addr_lo), "+y"(addr_mid)
               : [hi] "r"(addr_hi)
               : "p");
  return err;
}
