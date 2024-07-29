// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// MEGA65 DMA Audio example using C23

#include <mega65.h>

typedef unsigned _BitInt(24) uint24_t;

// Sample data prepared with:
// ~~~
// sox -v 2.0 -V -D drums.wav drums.s8 remix - lowpass 7000 rate -v -s -I 11822 dither -S
// ~~~
static const uint8_t sample[] = {
#embed "drums.s8"
};

int main(void) {
  DMA.ch0.enable = 0;                                 // mute channel 0
  DMA.auden = DMA_AUDEN;                              // enable DMA audio
  DMA.ch0.baddr = (uint24_t)&sample;                  // base address
  DMA.ch0.curaddr = (uint24_t)&sample;                // current address
  DMA.ch0.taddr = (uint16_t)&sample + sizeof(sample); // top address
  DMA.ch0.freq = 0x001a88;                            // frequency
  DMA.ch0.volume = 255;                               // max volume
  DMA.ch0.enable = DMA_CHENABLE ^ DMA_CHSBITS_8 ^ DMA_CHLOOP; // play!
}
