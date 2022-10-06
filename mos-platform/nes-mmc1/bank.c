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

static char PRG_BANK;
static char CHR_BANK0;
static char CHR_BANK1;
static char MMC1_CTRL_NMI;

char _CHR_BANK0_CUR;
extern __attribute__((weak, alias("_CHR_BANK0_CUR"))) volatile const char CHR_BANK0_CUR;
char _CHR_BANK1_CUR;
extern __attribute__((weak, alias("_CHR_BANK1_CUR"))) volatile const char CHR_BANK1_CUR;
char _MMC1_CTRL_CUR;
extern __attribute__((weak, alias("_MMC1_CTRL_CUR"))) volatile const char MMC1_CTRL_CUR;

#define MMC1_CTRL 0x8000
#define MMC1_CHR0 0xa000
#define MMC1_CHR1 0xc000
#define MMC1_PRG 0xe000

// Incrementing a 0xff ROM byte resets the MMC.
__attribute__((used)) static const char reset_mmc1_byte = 0xff;

static volatile char IN_PROGRESS = 0;

__attribute__((always_inline)) static inline void
mmc1_register_write(unsigned addr, char val) {
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
  val >>= 1;
  POKE(addr, val);
}

__attribute__((always_inline)) static inline void
mmc1_register_write_retry(unsigned addr, char val) {
  // May be interrupting another write, so reset the shift register.
  asm volatile("inc reset_mmc1_byte");
  do {
    IN_PROGRESS = 1;
    mmc1_register_write(addr, val);
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
  PRG_BANK = bank_id;
  mmc1_register_write_retry(MMC1_PRG, bank_id);
}

__attribute__((weak)) char get_prg_bank(void) { return PRG_BANK; }

__attribute__((weak)) void set_chr_bank_0(char bank_id) {
  CHR_BANK0 = bank_id;
}

__attribute__((weak)) void set_chr_bank_1(char bank_id) {
  CHR_BANK1 = bank_id;
}

__attribute__((weak)) void split_chr_bank_0(char bank_id) {
  asm volatile("inc reset_mmc1_byte");
  mmc1_register_write(MMC1_CHR0, bank_id);
  IN_PROGRESS = 0;
  _CHR_BANK0_CUR = bank_id;
}

__attribute__((weak)) void split_chr_bank_1(char bank_id) {
  asm volatile("inc reset_mmc1_byte");
  mmc1_register_write(MMC1_CHR1, bank_id);
  IN_PROGRESS = 0;
  _CHR_BANK1_CUR = bank_id;
}

__attribute__((weak)) void set_chr_bank_0_retry(char bank_id) {
  CHR_BANK0 = bank_id;
  mmc1_register_write_retry(MMC1_CHR0, bank_id);
}

__attribute__((weak)) void set_chr_bank_1_retry(char bank_id) {
  CHR_BANK1 = bank_id;
  mmc1_register_write_retry(MMC1_CHR1, bank_id);
}

__attribute__((weak)) void set_mirroring(char mirroring) {
  MMC1_CTRL_NMI &= 0b11100;
  MMC1_CTRL_NMI |= mirroring & 0b11;
}

__attribute__((weak)) void set_mmc1_ctrl(char value) {
  MMC1_CTRL_NMI = value;
  mmc1_register_write_retry(MMC1_CTRL, value);
  _MMC1_CTRL_CUR = value;
}

// some things deleted

void __nmi_bank_handler(void) {
  asm volatile("inc reset_mmc1_byte");
  mmc1_register_write(MMC1_CHR0, CHR_BANK0);
  _CHR_BANK0_CUR = CHR_BANK0;
  mmc1_register_write(MMC1_CHR1, CHR_BANK1);
  _CHR_BANK1_CUR = CHR_BANK0;
  mmc1_register_write(MMC1_CTRL, MMC1_CTRL_NMI);
  _MMC1_CTRL_CUR = MMC1_CTRL_NMI;
  IN_PROGRESS = 0;
}
__attribute__((weak, alias("__nmi_bank_handler"))) void nmi_bank_handler(void);
