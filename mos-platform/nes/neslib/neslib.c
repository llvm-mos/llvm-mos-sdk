// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// The MIT License (MIT)
// Copyright (c) 2018 Doug Fraker
// www.nesdoug.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Startup code for cc65 and Shiru's NES library
// based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz <uz@cc65.org>

// Keeping these functions in C LTOs them in, which informs LTO code generation
// that the ZP regions aren't available. This saves users of the library from
// having to manually reserve ZP space from LTO.
__attribute__((section(".zp.ntsc_mode"))) char NTSC_MODE;
__attribute__((section(".zp.frame_cnt1"))) char FRAME_CNT1;
__attribute__((section(".zp.frame_cnt2"))) char FRAME_CNT2;
__attribute__((section(".zp.vram_update"))) char VRAM_UPDATE;
__attribute__((section(".zp.name_upd_adr"))) char *NAME_UPD_ADR;
__attribute__((section(".zp.name_upd_enable"))) char NAME_UPD_ENABLE;
__attribute__((section(".zp.pal_update"))) char PAL_UPDATE;
__attribute__((section(".zp.pal_bg_ptr"))) char *PAL_BG_PTR;
__attribute__((section(".zp.pal_spr_ptr"))) char *PAL_SPR_PTR;
__attribute__((section(".zp.scroll_x"))) char SCROLL_X;
__attribute__((section(".zp.scroll_y"))) char SCROLL_Y;
__attribute__((section(".zp.scroll_x1"))) char SCROLL_X1;
__attribute__((section(".zp.scroll_y1"))) char SCROLL_Y1;
__attribute__((section(".zp.pad_state"))) char PAD_STATE[2];
__attribute__((section(".zp.pad_statep"))) char PAD_STATEP[2];
__attribute__((section(".zp.pad_statet"))) char PAD_STATET[2];
__attribute__((section(".zp.ppu_ctrl_var"))) char PPUCTRL_VAR;
__attribute__((section(".zp.ppu_ctrl_var1"))) char PPUCTRL_VAR1;
__attribute__((section(".zp.ppu_mask_var"))) char PPUMASK_VAR;
__attribute__((section(".zp.rand_seed"))) unsigned RAND_SEED;
__attribute__((section(".zp.sprid"))) unsigned SPRID;
