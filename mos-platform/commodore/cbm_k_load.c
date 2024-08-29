// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

// Helper to (dis)assemble a 16-bit integer
typedef union {
  uint16_t value;
  struct {
    uint8_t lo, hi;
  };
} Word;

void *cbm_k_load(const unsigned char flag, void *load_addr) {

  Word result;
  const Word addr = {.value = (uint16_t)(load_addr)};

  __attribute__((leaf)) __asm__ volatile(
      "    jsr __LOAD   \n"
      "    bcc 1f       \n" // no error if carry clear
      "    tax          \n" // else get error code from A
      "    ldy #0       \n"
      "1:               \n" // no error
      : "=x"(result.lo), "=y"(result.hi)
      : "a"(flag), "x"(addr.lo), "y"(addr.hi)
      : "p");

  return (void *)(result.value);
}
