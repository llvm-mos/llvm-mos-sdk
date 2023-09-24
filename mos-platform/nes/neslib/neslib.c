// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#define __NES__
#include "nes.h"

// Startup code for cc65 and Shiru's NES library
// based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz
// <uz@cc65.org>

// Keeping these functions in C LTOs them in, which informs LTO code generation
// that the ZP regions aren't available. This saves users of the library from
// having to manually reserve ZP space from LTO.
__attribute__((section(".zp.frame_cnt1"))) volatile char FRAME_CNT1;
__attribute__((section(".zp.frame_cnt2"))) volatile char FRAME_CNT2;
__attribute__((section(".zp.vram_update"))) volatile char VRAM_UPDATE;
__attribute__((section(".zp.scroll_x"))) volatile char SCROLL_X;
__attribute__((section(".zp.scroll_y"))) volatile char SCROLL_Y;
__attribute__((section(".zp.scroll_x1"))) volatile char SCROLL_X1;
__attribute__((section(".zp.scroll_y1"))) volatile char SCROLL_Y1;
__attribute__((section(".zp.pad_state"))) char PAD_STATE[2];
__attribute__((section(".zp.pad_statep"))) char PAD_STATEP[2];
__attribute__((section(".zp.pad_statet"))) char PAD_STATET[2];
__attribute__((section(".zp.ppu_ctrl_var"))) volatile char PPUCTRL_VAR;
__attribute__((section(".zp.ppu_ctrl_var1"))) volatile char PPUCTRL_VAR1;
__attribute__((section(".zp.ppu_mask_var"))) volatile char PPUMASK_VAR;

void ppu_wait_nmi(void);
void ppu_off(void) {
  PPUMASK_VAR &= 0b11100111;
  ppu_wait_nmi();
}
void ppu_on_all(void) {
  PPUMASK_VAR |= 0b00011000;
  ppu_wait_nmi();
}

void ppu_on_bg(void) {
  PPUMASK_VAR |= 0b00001000;
  ppu_wait_nmi();
}

void ppu_on_spr(void) {
  PPUMASK_VAR |= 0b00010000;
  ppu_wait_nmi();
}

void ppu_mask(char mask) { PPUMASK_VAR = mask; }

char pad_poll(char pad);
char pad_trigger(char pad) {
  pad_poll(pad);
  return PAD_STATET[pad];
}

char pad_state(char pad) { return PAD_STATE[pad]; }

void vram_adr(unsigned adr) {
  PPU.vram.address = adr >> 8;
  PPU.vram.address = adr & 0xff;
}

void vram_put(char n) { PPU.vram.data = n; }

void delay(char frames) {
  do
    ppu_wait_nmi();
  while (--frames);
}
