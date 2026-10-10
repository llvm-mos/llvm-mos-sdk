// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Store a byte to any MEGA65 bank via KERNAL STA_FAR ($FF77).
void mega65_k_sta_far(uint8_t bank, uint16_t addr, uint8_t y_offset,
                      uint8_t value) {
  uint8_t addr_lo = (uint8_t)addr;
  uint8_t addr_hi = (uint8_t)(addr >> 8);
  // See mega65_k_lda_far.c for the $FB/$FC scratch pair and the Z handling.
  asm volatile("stx $fb\n"
               "sty $fc\n"
               "taz\n"
               "lda %[val]\n"
               "ldy %[idx]\n"
               "ldx #$fb\n"
               "jsr __STA_FAR\n"
               "ldz #0\n"
               : "+a"(bank), "+x"(addr_lo), "+y"(addr_hi)
               : [idx] "r"(y_offset), [val] "r"(value)
               : "p");
}
