// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

/// Get cursor position relative to the active window (PLOT, $FFF0).
mega65_plot_t mega65_k_plot_get(void) {
  uint8_t l, c;
  asm volatile("sec\n"
               "jsr __PLOT"
               : "=x"(l), "=y"(c)
               :
               : "a", "p");
  return (mega65_plot_t){.line = l, .col = c};
}

/// Set cursor position relative to the active window (PLOT, $FFF0).
void mega65_k_plot_set(uint8_t line, uint8_t col) {
  // The set path falls through into the read path, which recomputes X and Y
  // from the cursor variables; X comes back one short of the line it was
  // given, so neither register survives the call intact.
  asm volatile("clc\n"
               "jsr __PLOT"
               : "+x"(line), "+y"(col)
               :
               : "a", "p");
}
