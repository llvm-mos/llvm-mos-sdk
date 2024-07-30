// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Vertical Raster Bars using the DMAgic DMA controller.
//
// - Timing is crucial: specify NTSC or PAL below.
// - Compile with `mos-mega65-clang++ -Os -flto`
// - Originally from ACME assembler example in the MEGA65 book
// - Converted to llvm-mos / C++ by Wombat, 2024.
// - As of writing (Summer 2024) this runs only on real hardware

#include <dma.hpp>
#include <mega65.h>

using namespace mega65;

constexpr bool PAL = true; // Set to false on NTSC systems

constexpr uint8_t RASTER_COLORS[] = {
    0,  1,  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,  4,  0,  1,  2,  3,  4,
    5,  0,  1,  2,  3,  4,  5,  6,  0,  1,  2,  3,  4,  5,  6,  7,  0,  1,  2,
    3,  4,  5,  6,  7,  8,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  1,  2,
    3,  4,  5,  6,  7,  8,  9,  10, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
    11, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 0,  1,  2,  3,  4,
    5,  6,  7,  8,  9,  10, 11, 12, 13, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
    13, 14, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  14,
    13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  13, 12, 11, 10, 9,
    8,  7,  6,  5,  4,  3,  2,  1,  0,  12, 11, 10, 9,  8,  7,  6,  5,  4,  3,
    2,  1,  0,  11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  10, 9,  8,  7,
    6,  5,  4,  3,  2,  1,  0,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  8,  7,
    6,  5,  4,  3,  2,  1,  0,  7,  6,  5,  4,  3,  2,  1,  0,  6,  5,  4,  3,
    2,  1,  0,  5,  4,  3,  2,  1,  0,  4,  3,  2,  1,  0,  3,  2,  1,  0,  2,
    1,  0,  1,  0,  0,  0,  0,  1,  0,  1,  2,  0,  1,  2,  3,  0,  1,  2,  3,
    4,  0,  1,  2,  3,  4,  5,  0,  1,  2,  3,  4,  5,  6,  0,  1,  2,  3,  4,
    5,  6,  7,  0,  1,  2,  3,  4,  5,  6,  7,  8,  0,  1,  2,  3,  4,  5,  6,
    7,  8,  9,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 0,  1,  2,  3,  4,
    5,  6,  7,  8,  9,  10, 11, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
    12, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 0,  1,  2,  3,
    4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 0,  0,  1,  2,  3,  4,  5,  6,
    7,  8,  9,  10, 11, 12, 13, 14, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,
    4,  3,  2,  1,  0,  14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,
    0,  13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  12, 11, 10, 9,
    8,  7,  6,  5,  4,  3,  2,  1,  0,  11, 10, 9,  8,  7,  6,  5,  4,  3,  2,
    1,  0,  10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0,  9,  8,  7,  6,  5,  4,
    3,  2,  1,  0,  8,  7,  6,  5,  4,  3,  2,  1,  0,  7,  6,  5,  4,  3,  2,
    1,  0,  6,  5,  4,  3,  2,  1,  0,  5,  4,  3,  2,  1,  0,  4,  3,  2,  1,
    0,  3,  2,  1,  0,  2,  1,  0,  1,  0,  0,  0,
};

int main() {
  asm volatile("sei"); // Disable interrupt to stabilise timing
  VICIV.ctrl1 = 0;     // Disable screen

  // Set custom color palette
  for (size_t i = 1; i < 16; i++) {
    PALETTE.red[i] = 15 - i;
    PALETTE.green[i] = 0;
    PALETTE.blue[i] = i;
  }

  // Configure DMA job; see The MEGA65 Book, Appendix O.
  dma::DMAJob<2, DMAList_F018A> dma;
  dma.options[0] = DST_ADDR_BITS_OPT;
  dma.options[1] = 0xff;
  dma.dmalist.command = DMA_COPY_CMD;
  dma.dmalist.count = PAL ? 628 : 624;
  dma.dmalist.source_addr = (uint16_t)&RASTER_COLORS;
  dma.dmalist.source_bank = 0x00;
  dma.dmalist.dest_addr = 0x0020;
  dma.dmalist.dest_bank = 0x0d ^ DMA_HOLD;
  dma.dmalist.modulo = 0;

  // Wait for new raster line
  const auto line = VICIV.rasterline;
  while (line == VICIV.rasterline)
    ;

#pragma clang loop unroll(disable)
  while (true) {
    dma::trigger_dma(dma);
    if constexpr (PAL) {
      asm volatile("nop");
    }
  }
}
