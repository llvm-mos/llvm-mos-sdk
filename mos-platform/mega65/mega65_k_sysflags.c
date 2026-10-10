// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

uint8_t mega65_k_sysflags_get(void) {
  uint8_t locks;
  asm volatile("sec\n"
               "jsr __SYSFLAGS"
               : "=a"(locks)
               :
               : "x", "y", "p");
  return locks;
}

void mega65_k_sysflags_set(uint8_t locks) {
  asm volatile("clc\n"
               "jsr __SYSFLAGS"
               :
               : "a"(locks)
               : "x", "y", "p");
}
