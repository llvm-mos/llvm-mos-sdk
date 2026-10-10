// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <mega65.h>

mega65_io_t mega65_k_getio(void) {
  uint8_t in, out;
  asm volatile("jsr __GETIO" : "=x"(in), "=y"(out) : : "a", "p");
  return (mega65_io_t){.input_dev = in, .output_dev = out};
}
