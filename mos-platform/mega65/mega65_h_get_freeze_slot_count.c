// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D642 (syspart): get_slot_count ($16).
//
// See mega65_h_locate_freezeslot.c on why the trap register differs.

#include <mega65.h>

uint16_t mega65_h_get_freeze_slot_count(void) {
  uint8_t count_lo, count_hi;

  // Count in X and Y, low first. No failure report: a machine without a
  // system partition answers zero.
  asm volatile("lda #$16\n"
               "sta $d642\n"
               "clv\n"
               : "=x"(count_lo), "=y"(count_hi)
               :
               : "a", "p");

  return (uint16_t)count_lo | ((uint16_t)count_hi << 8);
}
