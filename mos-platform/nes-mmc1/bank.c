// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.
//
// Copyright 2019 Doug Fraker
// Copyright 2018 Christopher Parker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "bank.h"

#include <peekpoke.h>

char _PRG_BANK;
extern __attribute__((weak, alias("_PRG_BANK"))) char PRG_BANK;
char _CHR_BANK0;
extern __attribute__((weak, alias("_CHR_BANK0"))) char CHR_BANK0;
char _CHR_BANK1;
extern __attribute__((weak, alias("_CHR_BANK1"))) char CHR_BANK1;
char _MIRROR;
extern __attribute__((weak, alias("_MIRROR"))) char MIRROR;

char _CHR_BANK0_CUR;
char _CHR_BANK1_CUR;

#define MMC1_CTRL 0x8000
#define MMC1_CHR0 0xa000
#define MMC1_CHR1 0xc000
#define MMC1_PRG 0xe000

// Incrementing a 0xff ROM byte resets the MMC.
__attribute__((used)) static const char reset_mmc1_byte = 0xff;

static volatile char IN_PROGRESS = 0;

__attribute__((always_inline)) static inline void
mmc1_register_write(unsigned addr, char val) {
  // Interrupted another write, so must reset the shift register.
  if (IN_PROGRESS)
    asm volatile("inc reset_mmc1_byte");
  IN_PROGRESS = 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  // Was interrupted, and we may have written a few bytes afterwards, so reset
  // the shift register.
  if (!IN_PROGRESS)
    asm volatile("inc reset_mmc1_byte");
  IN_PROGRESS = 0;
}

__attribute__((always_inline)) static inline void
mmc1_register_write_retry(unsigned addr, char val) {
  // If interrupting another write, must reset the shift register.
  if (IN_PROGRESS)
    asm volatile("inc reset_mmc1_byte");
  do {
    IN_PROGRESS = 1;
    POKE(addr, val);
    val >>= 1;
    POKE(addr, val);
    val >>= 1;
    POKE(addr, val);
    val >>= 1;
    POKE(addr, val);
    val >>= 1;
    POKE(addr, val);
    // Was interrupted, and we may have written a few bytes afterwards, so reset
    // the shift register and try again until successful.
    if (!IN_PROGRESS)
      asm volatile("inc reset_mmc1_byte");
  } while (!IN_PROGRESS);
  IN_PROGRESS = 0;
}

__attribute__((weak)) void banked_call(char bankId, void (*method)(void)) {
  char old_id = get_prg_bank();
  method();
  set_prg_bank(old_id);
}

__attribute__((weak)) void set_prg_bank(char bank_id) {
  _PRG_BANK = bank_id;
  mmc1_register_write_retry(MMC1_PRG, bank_id);
}

__attribute__((weak)) char get_prg_bank(void) { return _PRG_BANK; }

__attribute__((weak)) void set_chr_bank_0(char bank_id) {
  _CHR_BANK0 = bank_id;
}

__attribute__((weak)) void set_chr_bank_1(char bank_id) {
  _CHR_BANK1 = bank_id;
}

// Set by linker script. Mask where set bits indicate those bytes of the CHR
// bank register affect the actual CHR bank, rather than PRG.
extern char _CHR_BANK_MASK;
static char chr_mask(void) { return (char)(unsigned)&_CHR_BANK_MASK; }

static char apply_chr_mask(char cur, char new) {
  char mask = chr_mask();
  return cur & ~mask | new &mask;
}
static char apply_chr_mask_hi(char cur, char new) {
  char mask = chr_mask();
  return cur & mask | new & ~mask;
}

// Set the current 1st 4k chr bank to the bank with this id.
// this will take effect immediately, such as for mid screen changes
// but then will be overwritten by the set_chr_bank_0() value
// in the next frame.
__attribute__((weak)) void split_chr_bank_0(char bank_id) {
  _CHR_BANK0_CUR = apply_chr_mask(_CHR_BANK0_CUR, bank_id);
  mmc1_register_write(MMC1_CHR0, _CHR_BANK0_CUR);
}

// Set the current 2nd 4k chr bank to the bank with this id.
// this will take effect immediately, such as for mid screen changes
// but then will be overwritten by the set_chr_bank_1() value
// in the next frame.
__attribute__((weak)) void split_chr_bank_1(char bank_id) {
  _CHR_BANK1_CUR = apply_chr_mask(_CHR_BANK1_CUR, bank_id);
  mmc1_register_write(MMC1_CHR1, _CHR_BANK1_CUR);
}

// Immediately set the high bytes of CHR-ROM bank 0, those that don't affect
// CHR-ROM. Settings here are guaranteed to occur and to persist across NMIs.
__attribute__((weak)) void set_chr_bank_0_hi(char bank_id) {
  _CHR_BANK0_CUR = apply_chr_mask_hi(_CHR_BANK0_CUR, bank_id);
  mmc1_register_write_retry(MMC1_CHR0, _CHR_BANK0_CUR);
}

// Immediately set the high bytes of CHR-ROM bank 0, those that don't affect
// CHR-ROM. Settings here are guaranteed to occur and to persist across NMIs.
__attribute__((weak)) void set_chr_bank_1_hi(char bank_id) {
  _CHR_BANK0_CUR = apply_chr_mask_hi(_CHR_BANK1_CUR, bank_id);
  mmc1_register_write_retry(MMC1_CHR0, _CHR_BANK0_CUR);
}

// if you need to swap CHR banks mid screen, perhaps you need more
// than 256 unique tiles, first write (one time only) the CHR bank
// for the top of the screen with set_chr_bank_0().
// Then, every frame, time a mid screen split (probably with
// a sprite zero hit) and then change the CHR bank with
// split_chr_bank_0().
//
// example ---- in game loop
// split(0); ---- wait for sprite zero hit, set X scroll to 0
// split_chr_bank_0(6) ---- change CHR bank to #6

#define MIRROR_LOWER_BANK 0
#define MIRROR_UPPER_BANK 1
#define MIRROR_VERTICAL 2
#define MIRROR_HORIZONTAL 3

// Set the current mirroring mode. Your options are MIRROR_LOWER_BANK,
// MIRROR_UPPER_BANK, MIRROR_HORIZONTAL, and MIRROR_VERTICAL.
// LOWER and UPPER are single screen modes
__attribute__((weak)) void set_mirroring(char mirroring) {
  _MIRROR = mirroring & 0b00000011 | 0b00011100;
}

// Set all 5 bits of the $8000 MMC1 Control register (not recommended)
__attribute__((weak)) void set_mmc1_ctrl(char value) {
  _MIRROR = value & 0b00011111;
  mmc1_register_write(MMC1_CTRL, _MIRROR);
}

// some things deleted

void __nmi_bank_handler(void) {
  mmc1_register_write(MMC1_CHR0, apply_chr_mask(_CHR_BANK0_CUR, _CHR_BANK0));
  mmc1_register_write(MMC1_CHR1, apply_chr_mask(_CHR_BANK1_CUR, _CHR_BANK1));
  mmc1_register_write(MMC1_CTRL, _MIRROR);
}
__attribute__((weak, alias("__nmi_bank_handler"))) void nmi_bank_handler(void);
