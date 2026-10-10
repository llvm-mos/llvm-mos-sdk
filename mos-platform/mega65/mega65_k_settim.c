// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Set the CIA1 time-of-day clock (SETTIM, $FFDB).
/// All values are in BCD format (e.g. 0x59 = 59 decimal).
void mega65_k_settim(uint8_t hours, uint8_t minutes, uint8_t seconds,
                     uint8_t tenths) {
  // Tenths are passed in Z, so Z has to be restored to 0 before returning to
  // compiled code. SETTIM rewrites Y with the PM-adjusted hour.
  asm volatile("ldz %[tenths]\n"
               "jsr __SETTIM\n"
               "ldz #0\n"
               : "+y"(hours)
               : "a"(seconds), "x"(minutes), [tenths] "r"(tenths)
               : "p");
}
