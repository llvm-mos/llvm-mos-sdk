// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

// MEGA65 override of commodore cbm_k_save. SAVE leaves Z at 0 only as an
// artefact of its own [sal],z addressing; this wrapper clears it explicitly.
// Save memory to a file (SAVE, $FFD8).
// Requires cbm_k_setlfs() and cbm_k_setnam() called first.
// On MEGA65, also call mega65_k_setbnk() to set the data/filename banks.
// @param startaddr        Start of memory region to save.
// @param endaddr_plusone  First byte past the end (not saved).
// @return 0 on success, or KERNAL error code (1-9).
// Repeated from cbm.h, which callers compile against, because including it
// here needs __CBM__ and the platform build does not define it.
uint8_t cbm_k_save(void *startaddr, void *endaddr_plusone)
    __attribute__((leaf));

uint8_t cbm_k_save(void *startaddr, void *endaddr_plusone) {
  uint8_t end_lo = (uint8_t)(uint16_t)endaddr_plusone;
  uint8_t end_hi = (uint8_t)((uint16_t)endaddr_plusone >> 8);
  uint8_t err;
  // SAVE reads the start address through a zero-page pointer, so it must live
  // in one: an imaginary register pair is the cheapest such home, and
  // "lda #%[zp]" assembles to its zero-page address.
  uint16_t zp_ptr = (uint16_t)startaddr;

  // The save runs through X and Y, and the carry is consumed here because
  // "=c" outputs miscompile (see mega65_k_load.c).
  asm volatile("lda #%[zp]\n"
               "jsr __SAVE\n"
               "ldz #0\n"
               "bcs 1f\n"
               "lda #0\n"
               "1:\n"
               : "=&a"(err), [zp] "+r"(zp_ptr), "+x"(end_lo), "+y"(end_hi)
               :
               : "p");

  return err;
}
