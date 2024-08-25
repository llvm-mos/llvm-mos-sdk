// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>
#include <cx16.h>

uint8_t vpeek(const uint32_t address) {
  VERA.control = 0;
  VERA.address = (uint16_t)address;
  VERA.address_hi = (uint8_t)(address >> 16);
  return VERA.data0;
}
