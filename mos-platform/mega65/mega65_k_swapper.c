// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Toggle between 40x25 and 80x25 text modes (SWAPPER, $FF65).
void mega65_k_swapper(void) {
  // set_screen_mode leaves Z holding the x-scroll value.
  asm volatile("jsr __SWAPPER\n"
               "ldz #0"
               :
               :
               : "a", "x", "y", "p");
}
