// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Load or verify a file (LOAD, $FFD5). Supports MEGA65 raw mode (flag bit 6).
/// flag: 0x00=load, 0x01=verify, 0x40=raw load, 0x41=raw verify.
/// Raw mode treats the first two bytes as data instead of a PRG header.
/// Requires SETBNK, SETLFS, SETNAM called first.
/// @return 0 on success (writes *end_addr), or KERNAL error code (1-9).
uint8_t mega65_k_load(uint8_t flag, void *load_addr, void **end_addr) {
  uint8_t addr_lo = (uint8_t)(uint16_t)load_addr;
  uint8_t addr_hi = (uint8_t)((uint16_t)load_addr >> 8);
  uint8_t end_lo, end_hi, err;

  // The carry must be tested inside the block. An "=c" output miscompiles:
  // on clang 22 it aborts the LTO link outright, and on later versions it
  // trips a register-scavenger assertion once the program is big enough.
  // LOAD leaves Z at 0 on the slow and burst paths but at 3 on the FastLoad
  // path, so it always has to be cleared.
  asm volatile("jsr __LOAD\n"
               "bcs 1f\n"
               "lda #0\n"
               "1:\n"
               "ldz #0"
               : "=a"(err), "=x"(end_lo), "=y"(end_hi)
               : "a"(flag), "x"(addr_lo), "y"(addr_hi)
               : "p");
  if (!err) {
    *end_addr = (void *)((uint16_t)end_hi << 8 | end_lo);
  }
  return err;
}
