// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <cx16.h>
#include <stdint.h>

void cx16_k_screen_set_charset(const unsigned char charset_type, void *ptr) {
  const uint16_t addr = (uint16_t)(ptr);
  __attribute__((lead)) __asm__ volatile(
      "jsr __SCREEN_SET_CHARSET\n" ::"a"(charset_type), "x"((uint8_t)(addr)),
      "y"((uint8_t)(addr >> 8))
      : "c", "v");
}
