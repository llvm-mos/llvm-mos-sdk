// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D642 (syspart): locate_freezeslot ($10).
//
// The address picks the handler, so $D642 numbers its functions separately
// from the $D640 used elsewhere here.

#include <mega65.h>

/// Where hyppo leaves the sector number. Little-endian, matching uint32_t.
#define SD_SECTOR_NUMBER 0xd681

uint32_t mega65_h_locate_freezeslot(uint16_t slot) {
  uint8_t slot_lo = (uint8_t)slot;
  uint8_t slot_hi = (uint8_t)(slot >> 8);

  // Low byte in Y, against hyppo's own comment: it pushes X then Y and pops
  // with plx/ply, so Y comes back first and becomes the low byte. Follow the
  // arithmetic, which decides the answer.
  //
  // No carry to read: this trap leaves the caller's flags alone, so a bad
  // slot looks like a good one.
  //
  // "memory" because the answer lands in I/O the compiler cannot see.
  asm volatile("lda #$10\n"
               "sta $d642\n"
               "clv\n"
               :
               : "y"(slot_lo), "x"(slot_hi)
               : "a", "p", "memory");

  return *(const volatile uint32_t *)SD_SECTOR_NUMBER;
}
