// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <dma.hpp>
#include <mega65.h>

using namespace mega65::dma;

constexpr uint32_t DST = 0x0800; // Address of default screen
constexpr uint16_t COUNT = 4;

/// "DMA" is a volatile ref.
template <typename T> void trigger(T dma) {
  DMA.enable_f018b = true;
  DMA.addr_bank = 0;
  DMA.addr_msb = ((uint16_t)(&dma)) >> 8;
  DMA.trigger_enhanced = ((uint16_t)(&dma)) & 0xff; // <- triggers DMA job
}

int main(void) {
  {
    auto dma = make_dma_fill(DST, 21, COUNT);
    trigger(dma);
  }
  {
    auto dma = make_dma_copy(DST, DST + COUNT, COUNT);
    trigger(dma);
  }
  while (true) {
    asm volatile("");
  }
}
