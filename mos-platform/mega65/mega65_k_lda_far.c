// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Read a byte from any MEGA65 bank via KERNAL LDA_FAR ($FF74).
uint8_t mega65_k_lda_far(uint8_t bank, uint16_t addr, uint8_t y_offset) {
  uint8_t addr_lo = (uint8_t)addr;
  uint8_t addr_hi = (uint8_t)(addr >> 8);
  uint8_t result;
  // LDA_FAR wants the address in a zero-page pair pointed to by X. $FB/$FC is
  // free on both sides: the ROM's base-page allocations end at $FA, and the
  // compiler's zero page ends at $8F. The bank goes in Z, and LDA_FAR hands
  // Z back as it found it, so it has to be cleared before returning.
  asm volatile("stx $fb\n"
               "sty $fc\n"
               "taz\n"
               "ldy %[idx]\n"
               "ldx #$fb\n"
               "jsr __LDA_FAR\n"
               "ldz #0\n"
               : "=a"(result), "+x"(addr_lo), "+y"(addr_hi)
               : "a"(bank), [idx] "r"(y_offset)
               : "p");
  return result;
}
