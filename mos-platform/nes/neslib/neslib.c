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
__attribute__((section(".zp.name_upd_adr"))) volatile const char *NAME_UPD_ADR;
__attribute__((section(".zp.name_upd_enable"))) volatile char NAME_UPD_ENABLE;
__attribute__((section(".zp.pal_update"))) volatile char PAL_UPDATE;
__attribute__((section(".zp.pal_bg_ptr"))) volatile const char *PAL_BG_PTR;
__attribute__((section(".zp.pal_spr_ptr"))) volatile const char *PAL_SPR_PTR;
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
__attribute__((section(".zp.sprid"))) unsigned SPRID;

extern volatile char PAL_BUF[];
void pal_col(char index, char color) {
  PAL_BUF[index & 0x1f] = color;
  ++PAL_UPDATE;
}

extern const char __palBrightTableL[];
extern const char __palBrightTableH[];
void pal_spr_bright(char bright) {
  PAL_SPR_PTR = (const char *)(__palBrightTableH[bright] << 8 |
                               __palBrightTableL[bright]);
  PAL_UPDATE = 1;
}
void pal_bg_bright(char bright) {
  PAL_BG_PTR = (const char *)(__palBrightTableH[bright] << 8 |
                              __palBrightTableL[bright]);
  PAL_UPDATE = 1;
}
void pal_bright(char bright) {
  pal_spr_bright(bright);
  pal_bg_bright(bright);
}

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

void oam_set(char index) { SPRID = index & 0xfc; }

char oam_get(void) { return SPRID; }

char pad_poll(char pad);
char pad_trigger(char pad) {
  pad_poll(pad);
  return PAD_STATET[pad];
}

char pad_state(char pad) { return PAD_STATE[pad]; }

void set_vram_update(const void *buf) {
  NAME_UPD_ADR = buf;
  NAME_UPD_ENABLE = NAME_UPD_ADR != 0;
}

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
