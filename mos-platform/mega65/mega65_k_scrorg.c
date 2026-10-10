// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Get screen window size and properties (SCRORG, $FFED).
mega65_screen_info_t mega65_k_scrorg(void) {
  mega65_screen_info_t info;
  // SCRORG answers in all four registers plus the carry: A/Z are the window
  // address, X/Y its size, C the 40-column flag. Z has to be emptied and
  // cleared before returning to compiled code, and the carry consumed here
  // because "=c" outputs miscompile (see mega65_k_load.c).
  asm volatile("jsr __SCREEN\n"
               "pha\n"
               "tza\n"
               "ldz #0\n"
               "sta %[hi]\n"
               "lda #0\n"
               "bcc 1f\n"
               "lda #1\n"
               "1:\n"
               "sta %[wide]\n"
               "pla\n"
               : "=a"(info.addr_lo), "=x"(info.max_col), "=y"(info.max_row),
                 [hi] "=&r"(info.addr_hi), [wide] "=&r"(info.is_40col)
               :
               : "p");
  return info;
}
