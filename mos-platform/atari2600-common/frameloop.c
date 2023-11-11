// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "vcslib.h"

void kernel_1(void) {
  // Vertical Sync signal
  TIA.vsync = START_VERT_SYNC;
  TIA.wsync = 0x00;
  // Test reset switch
  if (SW_RESET()) {
    asm("brk");
  }
  TIA.wsync = 0x00;
  TIA.wsync = 0x00;
  TIA.vsync = STOP_VERT_SYNC;

  // Vertical Blank (preframe)
  RIOT.tim64t = VBLANK_TIM64;
}

void kernel_2(void) {
  while (RIOT.intim != 0) {}

  // Turn on beam
  TIA.wsync = 0x00;
  TIA.vblank = ENABLE_TIA;

  // Display frame (doframe)
  #ifdef PAL
  RIOT.t1024t = KERNAL_T1024;
  #else
  RIOT.tim64t = KERNAL_TIM64;
  #endif
}

void kernel_3(void) {
  while (RIOT.intim != 0) {}

  // Turn off beam
  TIA.wsync = 0x00;
  TIA.vblank = DISABLE_TIA;

  // Overscan (postframe)
  RIOT.tim64t = OVERSCAN_TIM64;
}

void kernel_4(void) {
  while (RIOT.intim != 0) {}
}
