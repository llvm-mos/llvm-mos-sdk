// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Virtualises the F011 floppy controller with D81 images from SD card.
// Drive 0 = unit 8, drive 1 = unit 9 (by default).
//
// Trap $D640: attach ($4A).
// For attach: call mega65_h_setname() with the image filename first.
// Cannot open files inside disk images -- use KERNAL/F011 for that.

#include <mega65.h>

mega65_h_err mega65_h_attach(uint8_t flags) {
  uint8_t err;
  // Carry consumed inside the block; see mega65_k_load.c for why.
  asm volatile("lda #$4a\n"
               "sta $d640\n"
               "clv\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+x"(flags)
               :
               : "y", "p");
  return err;
}
