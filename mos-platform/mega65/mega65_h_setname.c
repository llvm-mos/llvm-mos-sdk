// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Stages a filename where Hyppo can read it, then names the page.
// Shared prerequisite for loadfile, findfile, dirio, and attach workflows.

#include <mega65.h>
#include <stdint.h>

/// Longest name Hyppo accepts, excluding the terminator.
#define NAME_LEN_MAX 63

/// The staging page, placed by the linker script rather than by this file:
/// which page is free is a property of the program, not of the wrapper. A
/// program holding two names at once -- one naming a file being loaded over
/// itself, one naming an image still to be attached -- needs two pages and
/// mega65_h_setname_page() for the second.
extern char __mega65_h_name_buf[256];

mega65_h_err mega65_h_setname(const char *filename) {
  char *buf = __mega65_h_name_buf;
  uint8_t i = 0;
  while (filename[i] && i < NAME_LEN_MAX) {
    buf[i] = filename[i];
    ++i;
  }
  buf[i] = 0;

  return mega65_h_setname_page((uint8_t)((uintptr_t)__mega65_h_name_buf >> 8));
}
