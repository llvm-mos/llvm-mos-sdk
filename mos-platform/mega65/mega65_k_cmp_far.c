// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Compare a byte with any MEGA65 bank via KERNAL CMP_FAR ($FF7A).
/// @return 0 if equal, 1 if not equal.
uint8_t mega65_k_cmp_far(uint8_t bank, uint16_t addr, uint8_t y_offset,
                         uint8_t value) {
  uint8_t addr_lo = (uint8_t)addr;
  uint8_t addr_hi = (uint8_t)(addr >> 8);
  uint8_t result;
  // See mega65_k_lda_far.c for the $FB/$FC scratch pair and the Z handling.
  // CMP_FAR answers in the status register, so the comparison is turned into
  // a value here rather than through a flag output constraint.
  asm volatile("stx $fb\n"
               "sty $fc\n"
               "taz\n"
               "lda %[val]\n"
               "ldy %[idx]\n"
               "ldx #$fb\n"
               "jsr __CMP_FAR\n"
               "beq 1f\n"
               "lda #1\n"
               "bra 2f\n"
               "1:\n"
               "lda #0\n"
               "2:\n"
               "ldz #0\n"
               : "=a"(result), "+x"(addr_lo), "+y"(addr_hi)
               : "a"(bank), [idx] "r"(y_offset), [val] "r"(value)
               : "p");
  return result;
}
