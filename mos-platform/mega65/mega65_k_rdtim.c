// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Read the CIA1 time-of-day clock (RDTIM, $FFDE).
/// All values are in BCD format (e.g. 0x59 = 59 decimal).
mega65_tod_t mega65_k_rdtim(void) {
  mega65_tod_t tod;
  // Tenths are returned in Z, which has to be emptied and cleared before
  // returning to compiled code. Reading the tenths register also releases the
  // TOD latch, so it must be read last.
  asm volatile("jsr __RDTIM\n"
               "pha\n"
               "tza\n"
               "ldz #0\n"
               "sta %[tenths]\n"
               "pla\n"
               : "=a"(tod.seconds), "=x"(tod.minutes),
                 "=y"(tod.hours), [tenths] "=&r"(tod.tenths)
               :
               : "p");
  return tod;
}
