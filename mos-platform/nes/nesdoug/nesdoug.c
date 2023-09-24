// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Startup code for cc65 and Shiru's NES library
// based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz
// <uz@cc65.org>

extern char PAD_STATET[];
char get_pad_new(char pad) { return PAD_STATET[pad]; }

extern volatile char FRAME_CNT1;
char get_frame_count(void) { return FRAME_CNT1; }

extern volatile char __FT_SONG_SPEED;
void set_music_speed(char tempo) { __FT_SONG_SPEED = tempo; }

extern volatile char PPUCTRL_VAR;
extern volatile char SCROLL_X;
void set_scroll_x(unsigned x) {
  SCROLL_X = x & 0xff;
  PPUCTRL_VAR = PPUCTRL_VAR & 0xfe | x >> 8 & 0x01;
}

extern volatile char SCROLL_Y;
void set_scroll_y(unsigned y) {
  SCROLL_Y = y;
  PPUCTRL_VAR = PPUCTRL_VAR & 0xfd | (y >> 8 & 0x01) << 1;
}

extern volatile char PPUMASK_VAR;
void color_emphasis(char color) {
  PPUMASK_VAR = PPUMASK_VAR & 0x1f | color & 0xe0;
}

extern volatile char FRAME_CNT1;
extern volatile char RAND_SEED;
void seed_rng(void) { RAND_SEED = FRAME_CNT1; }
