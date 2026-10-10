// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D642 (syspart): unfreeze_from_slot ($12).
//
// See mega65_h_locate_freezeslot.c on why the trap register differs.

#include <mega65.h>

void mega65_h_unfreeze_from_slot(uint16_t slot) {
  uint8_t slot_lo = (uint8_t)slot;
  uint8_t slot_hi = (uint8_t)(slot >> 8);

  // Bytes go where mega65_h_locate_freezeslot puts them, since hyppo hands
  // both traps to the same routine. That trap restores X and Y from the saved
  // registers; this one restores only X, and does not need to restore Y --
  // the trap dispatch clobbers X with tax and never touches Y, so the low byte
  // arrives on its own.
  //
  // Control does not come back if this succeeds: hyppo restores the frozen
  // program over this one, so the next line runs only on failure.
  asm volatile("lda #$12\n"
               "sta $d642\n"
               "clv\n"
               :
               : "y"(slot_lo), "x"(slot_hi)
               : "a", "p", "memory");
}
