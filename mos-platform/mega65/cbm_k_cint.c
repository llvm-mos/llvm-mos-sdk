// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// MEGA65 override of commodore cbm_k_cint. CINT copies the mouse window with
// ldq/stq, which loads Z; compiled code needs Z back at 0.
// Initialize the screen editor and VIC-IV (CINT, $FF81).
// Resets screen geometry, cursor position, and character set.
void cbm_k_cint(void) {
  asm volatile("jsr __CINT\n"
               "ldz #0"
               :
               :
               : "a", "x", "y", "p");
}
