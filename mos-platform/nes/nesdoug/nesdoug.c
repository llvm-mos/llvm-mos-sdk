// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Startup code for cc65 and Shiru's NES library
// based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz
// <uz@cc65.org>

// Keeping these functions in C LTOs them in, which informs LTO code generation
// that the ZP regions aren't available. This saves users of the library from
// having to manually reserve ZP space from LTO.

#include "nesdoug.h"

__attribute__((section(".zp.vram_index"))) char VRAM_INDEX;
__attribute__((section(".zp.meta_ptr"))) const char *META_PTR;
__attribute__((section(".zp.data_ptr"))) const char *DATA_PTR;
__attribute__((section(".zp.name_upd_adr"))) volatile const char *NAME_UPD_ADR;
__attribute__((section(".zp.name_upd_enable"))) volatile char NAME_UPD_ENABLE;


extern char VRAM_BUF[];

void set_nametable_update(const void *buf) {
  NAME_UPD_ADR = buf;
  NAME_UPD_ENABLE = NAME_UPD_ADR != 0;
}

void set_nametable_buffer(void) {
  VRAM_BUF[0] = 0xff;
  VRAM_INDEX = 0;
  set_nametable_update(VRAM_BUF);
}
__attribute((always_inline)) void nametable_buffer_copy(nametable_dir dir,
                                                        const void *data,
                                                        int ppu_address,
                                                        char len) {
  nametable_buffer_copy_op(dir | nametable_op_copy, data, ppu_address, len);
}

__attribute__((always_inline)) void
nametable_buffer_copy_horz(const void *data, int ppu_address, char len) {
  nametable_buffer_copy(nametable_dir_horz, data, ppu_address, len);
}

__attribute__((always_inline)) void
nametable_buffer_copy_vert(const void *data, int ppu_address, char len) {
  nametable_buffer_copy(nametable_dir_vert, data, ppu_address, len);
}

__attribute__((deprecated, always_inline)) void set_vram_update(const void *buf) {
  set_nametable_update(buf);
}

__attribute__((deprecated, always_inline)) void set_vram_buffer(void) {
  set_nametable_buffer();
}

__attribute__((deprecated, always_inline)) void one_vram_buffer(char data, int ppu_address) {
  nametable_buffer_one(data, ppu_address);
}

__attribute__((deprecated, always_inline)) void
multi_vram_buffer_horz(const void *data, char len, int ppu_address) {
  nametable_buffer_copy_horz(data, ppu_address, len);
}

__attribute__((deprecated, always_inline)) void
multi_vram_buffer_vert(const void *data, char len, int ppu_address) {
  nametable_buffer_copy_vert(data, ppu_address, len);
}

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

void set_data_pointer(const void *data) { DATA_PTR = (const char *)data; }
void set_mt_pointer(const void *metatiles) {
  META_PTR = (const char *)metatiles;
}

extern volatile char PPUMASK_VAR;
void color_emphasis(char color) {
  PPUMASK_VAR = PPUMASK_VAR & 0x1f | color & 0xe0;
}

extern volatile char FRAME_CNT1;
extern volatile char RAND_SEED;
void seed_rng(void) { RAND_SEED = FRAME_CNT1; }
