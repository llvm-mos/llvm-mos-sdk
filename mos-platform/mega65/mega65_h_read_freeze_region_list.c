// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D642 (syspart): read_freeze_region_list ($14).
//
// See mega65_h_locate_freezeslot.c on why the trap register differs.

#include <mega65.h>

mega65_h_err mega65_h_read_freeze_region_list(void *dest) {
  uint8_t dest_lo = (uint8_t)(uint16_t)dest;
  uint8_t dest_hi = (uint8_t)((uint16_t)dest >> 8);
  uint8_t err;

  // A full address, not a page. Hyppo clears the top bit to keep the copy
  // away from its own memory, so $8000 and up quietly land 32KB lower.
  //
  // Carry consumed inside the block; see mega65_k_load.c for why. "memory"
  // because hyppo writes where the compiler cannot see.
  asm volatile("lda #$14\n"
               "sta $d642\n"
               "clv\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err)
               : "x"(dest_lo), "y"(dest_hi)
               : "p", "memory");
  return err;
}
