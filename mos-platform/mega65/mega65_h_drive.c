// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// "Drives" in Hyppo are SD card partitions, not F011 floppy drives.
//
// Trap $D640: getcurrentdrive ($04), getdefaultdrive ($02), selectdrive ($06).

#include <mega65.h>

uint8_t mega65_h_getcurrentdrive(void) {
  uint8_t drive;
  asm volatile("lda #$04\n"
               "sta $d640\n"
               "clv\n"
               : "=a"(drive)
               :
               : "x", "y", "p");
  return drive;
}

uint8_t mega65_h_getdefaultdrive(void) {
  uint8_t drive;
  asm volatile("lda #$02\n"
               "sta $d640\n"
               "clv\n"
               : "=a"(drive)
               :
               : "x", "y", "p");
  return drive;
}

mega65_h_err mega65_h_selectdrive(uint8_t drive) {
  uint8_t err;
  // Carry consumed inside the block; see mega65_k_load.c for why.
  asm volatile("lda #$06\n"
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
