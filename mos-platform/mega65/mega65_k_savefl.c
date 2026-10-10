// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

#include <stdbool.h>

/// Save memory to a file with optional raw mode (SAVEFL, $FF3B).
/// In raw mode, the two-byte PRG address header is omitted.
/// The memory region must fit within a single bank.
/// Requires SETBNK, SETLFS, SETNAM called first.
/// @return 0 on success, or KERNAL error code (1-9).
uint8_t mega65_k_savefl(const void *start_addr, const void *end_addr_plus1,
                        bool raw) {
  uint8_t end_lo = (uint8_t)(uint16_t)end_addr_plus1;
  uint8_t end_hi = (uint8_t)((uint16_t)end_addr_plus1 >> 8);
  uint8_t flags = raw ? 0x40 : 0x00;
  uint8_t err;
  // SAVEFL reads the start address through a zero-page pointer, so it must
  // live in one: an imaginary register pair is the cheapest such home, and
  // "lda #%[zp]" assembles to its zero-page address.
  uint16_t zp_ptr = (uint16_t)start_addr;

  // Flags are passed in Z, so Z has to be restored to 0 before returning to
  // compiled code. The save itself runs through X and Y, and the carry is
  // carry consumed inside the block; see mega65_k_load.c for why.
  asm volatile("lda %[flags]\n"
               "taz\n"
               "lda #%[zp]\n"
               "jsr __SAVEFL\n"
               "ldz #0\n"
               "bcs 1f\n"
               "lda #0\n"
               "1:\n"
               : "=&a"(err), [zp] "+r"(zp_ptr), "+x"(end_lo), "+y"(end_hi)
               : [flags] "r"(flags)
               : "p");

  return err;
}
