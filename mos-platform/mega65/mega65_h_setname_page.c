// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Names an already-staged filename buffer to Hyppo.
//
// Trap $D640: setname ($2E).
//
// Its own translation unit so that a program staging its own page never links
// mega65_h_setname()'s copy loop.

#include <mega65.h>

mega65_h_err mega65_h_setname_page(uint8_t page) {
  uint8_t err;
  // Carry consumed inside the block; see mega65_k_load.c for why.
  //
  // "memory" because hyppo reads the page the caller just filled, and this
  // block inlines into that caller: volatile alone orders this against other
  // volatile accesses, not against the plain stores that staged the name.
  asm volatile("lda #$2e\n"
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
