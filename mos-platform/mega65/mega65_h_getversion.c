// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Trap $D640: getversion ($00).

#include <mega65.h>

mega65_h_version mega65_h_getversion(void) {
  uint8_t hyppo_major, hyppo_minor, hdos_major, hdos_minor;
  // getversion is the one service that answers in all four registers. The
  // fourth has to be moved out of Z before returning to compiled code, and A
  // is already spoken for, hence the pha/pla. Register outputs only: an "=m"
  // operand silently addresses the wrong memory once a local lands on the
  // soft stack.
  asm volatile("lda #$00\n"
               "sta $d640\n"
               "clv\n"
               "pha\n"
               "tza\n"
               "sta %[dosmin]\n"
               "ldz #0\n"
               "pla\n"
               : "=a"(hyppo_major), "=x"(hyppo_minor),
                 "=y"(hdos_major), [dosmin] "=&r"(hdos_minor)
               :
               : "p");
  return (mega65_h_version){.hyppo_major = hyppo_major,
                            .hyppo_minor = hyppo_minor,
                            .hdos_major = hdos_major,
                            .hdos_minor = hdos_minor};
}
