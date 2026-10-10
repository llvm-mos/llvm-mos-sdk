// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Copies the running program's task descriptor out to a page the caller names.
//
// Trap $D640: get_proc_desc ($48).

#include <mega65.h>

mega65_h_err mega65_h_get_proc_desc(uint8_t page) {
  uint8_t err;
  // Carry consumed inside the block; see mega65_k_load.c for why.
  //
  // "memory" because hyppo writes the page where the compiler cannot see.
  asm volatile("lda #$48\n"
               "sta $d640\n"
               "clv\n"
               "bcc 1f\n"
               "lda #0\n"
               "1:\n"
               : "=a"(err), "+y"(page)
               :
               : "x", "p", "memory");
  return err;
}
