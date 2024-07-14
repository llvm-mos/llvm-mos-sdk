// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <dma.hpp>
#include <mega65.h>

using namespace mega65::dma;

constexpr uint32_t SCREEN_ADDR = 0x0800; // Screen area
constexpr uint16_t COUNT = 4;            // Number of bytes to fill/copy

int main(void) {
  {
    // repeat some chars on first line
    const auto dma = make_dma_fill(SCREEN_ADDR, 41, COUNT);
    trigger_dma(dma);
  }
  {
    // copy first line to second line
    const auto dma = make_dma_copy(SCREEN_ADDR, SCREEN_ADDR + 80, 80);
    trigger_dma(dma);
  }
}
