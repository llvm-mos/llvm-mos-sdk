// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Set bank for LOAD/SAVE/VERIFY/OPEN data and filename addresses (SETBNK,
/// $FF6B).
void mega65_k_setbnk(uint8_t mem_bank, uint8_t fn_bank) {
  // SETBNK ends with "txa", so A does not survive the call.
  asm volatile("jsr __SETBNK" : "+a"(mem_bank) : "x"(fn_bank) : "y", "p");
}

/// Set 28-bit bank for LOAD/SAVE/VERIFY/OPEN data and filename addresses
/// (SETBNK, $FF6B).
void mega65_k_setbnk_28(uint8_t mem_mb, uint8_t mem_hi, uint8_t fn_mb,
                        uint8_t fn_hi) {
  // Bit 7 signals 28-bit mode to the KERNAL
  uint8_t a = 0x80 | mem_mb;
  uint8_t x = 0x80 | fn_mb;
  // The filename bank byte is passed in Z, so Z has to be restored to 0
  // before returning to compiled code. A does not survive ("txa").
  asm volatile("ldz %[fnhi]\n"
               "jsr __SETBNK\n"
               "ldz #0\n"
               : "+a"(a)
               : "x"(x), "y"(mem_hi), [fnhi] "r"(fn_hi)
               : "p");
}
