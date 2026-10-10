// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

mega65_lfs_t mega65_k_getlfs(void) {
  uint8_t a, x, y;
  asm volatile("jsr __GETLFS" : "=a"(a), "=x"(x), "=y"(y) : : "p");
  return (mega65_lfs_t){.la = a, .fa = x, .sa = y};
}
