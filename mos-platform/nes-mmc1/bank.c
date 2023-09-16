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

// Always bring in the NMI handler
asm(".globl bank_nmi");

__attribute__((section(".zp.bss"))) volatile char _CHR_BANK0_NEXT;
__attribute__((section(".zp.bss"))) volatile char _CHR_BANK1_NEXT;
__attribute__((section(".zp.data"))) volatile char _MMC1_CTRL_NEXT =
    CHR_ROM_BANK_MODE_4 | MIRROR_VERTICAL;

__attribute__((section(".zp.bss"))) volatile char _PRG_BANK;
__attribute__((section(".zp.bss"))) volatile char _CHR_BANK0;
__attribute__((section(".zp.bss"))) volatile char _CHR_BANK1;
__attribute__((section(".zp.data"))) volatile char _MMC1_CTRL =
    PRG_ROM_BANK_MODE_FIXED_C000;
__attribute__((section(".zp.bss"))) volatile char _IN_PROGRESS;

#define MMC1_CTRL 0x8000
#define MMC1_CHR0 0xa000
#define MMC1_CHR1 0xc000
#define MMC1_PRG 0xe000

#define DISABLE_IRQ() asm volatile("php\nsei")
#define RESTORE_IRQ() asm volatile("plp")

// Incrementing a 0xff ROM byte resets the MMC.
__attribute__((used)) const char __reset_mmc1_byte = 0xff;
static void reset_shift_register(void) {
  __attribute__((leaf)) asm volatile("inc __reset_mmc1_byte");
}

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
  do {
    _IN_PROGRESS = 1;
    reset_shift_register();
    mmc1_register_write(addr, val);
  } while (!_IN_PROGRESS);
  _IN_PROGRESS = 0;
}

char get_prg_bank(void) { return _PRG_BANK; }
__attribute__((alias("get_prg_bank"))) char __get_prg_bank(void);

void set_chr_bank_0(char bank_id) {
  defer_chr_bank_0(bank_id);
  split_chr_bank_0(bank_id);
}

void set_chr_bank_1(char bank_id) {
  defer_chr_bank_1(bank_id);
  split_chr_bank_1(bank_id);
}

void split_chr_bank_0(char bank_id) {
  DISABLE_IRQ();
  reset_shift_register();
  mmc1_register_write(MMC1_CHR0, bank_id);
  if (_IN_PROGRESS)
    _CHR_BANK0 = bank_id;
  RESTORE_IRQ();
  _IN_PROGRESS = 0;
}

void defer_chr_bank_0(char bank_id) { _CHR_BANK0_NEXT = bank_id; }

void defer_chr_bank_1(char bank_id) { _CHR_BANK1_NEXT = bank_id; }

void split_chr_bank_1(char bank_id) {
  DISABLE_IRQ();
  reset_shift_register();
  mmc1_register_write(MMC1_CHR1, bank_id);
  if (_IN_PROGRESS)
    _CHR_BANK1 = bank_id;
  RESTORE_IRQ();
  _IN_PROGRESS = 0;
}

extern char __chr_high_mask[];
extern char __chr_low_mask[];

char get_chr_bank_0_high(void) { return _CHR_BANK0 & (char)(__chr_high_mask); }

void set_chr_bank_0_high(char bank_id) {
  char s = _CHR_BANK0 & (char)(__chr_low_mask) | bank_id;
  mmc1_register_write_retry(MMC1_CHR0, s);
  _CHR_BANK0 = s;
}

char get_chr_bank_1_high(void) { return _CHR_BANK1 & (char)(__chr_high_mask); }

void set_chr_bank_1_high(char bank_id) {
  char s = _CHR_BANK1 & (char)(__chr_low_mask) | bank_id;
  mmc1_register_write_retry(MMC1_CHR1, s);
  _CHR_BANK1 = s;
}

void set_mirroring(enum Mirroring mirroring) {
  defer_mirroring(mirroring);
  split_mirroring(mirroring);
}

void split_mirroring(enum Mirroring mirroring) {
  char s = _MMC1_CTRL & 0b11100 | mirroring;
  DISABLE_IRQ();
  reset_shift_register();
  mmc1_register_write(MMC1_CTRL, s);
  if (_IN_PROGRESS)
    _MMC1_CTRL = s;
  RESTORE_IRQ();
  _IN_PROGRESS = 0;
}

void defer_mirroring(enum Mirroring mirroring) {
  _MMC1_CTRL_NEXT = _MMC1_CTRL_NEXT & 0b01111 | mirroring;
}

void set_chr_rom_bank_mode(enum ChrRomBankMode mode) {
  defer_chr_rom_bank_mode(mode);
  split_chr_rom_bank_mode(mode);
}

void split_chr_rom_bank_mode(enum ChrRomBankMode mode) {
  char s = _MMC1_CTRL & 0b01111 | mode;
  DISABLE_IRQ();
  reset_shift_register();
  mmc1_register_write(MMC1_CTRL, s);
  if (_IN_PROGRESS)
    _MMC1_CTRL = s;
  RESTORE_IRQ();
  _IN_PROGRESS = 0;
}

void defer_chr_rom_bank_mode(enum ChrRomBankMode mode) {
  _MMC1_CTRL_NEXT = _MMC1_CTRL_NEXT & 0b11100 | mode;
}

void set_prg_rom_bank_mode(enum PrgRomBankMode mode) {
  char s = _MMC1_CTRL & 0b10011 | mode;
  mmc1_register_write_retry(MMC1_CTRL, s);
  _MMC1_CTRL = s;
}

enum PrgRomBankMode get_prg_rom_bank_mode(void) { return _MMC1_CTRL & 0b01100; }

void set_mmc1_ctrl(char value) {
  defer_mmc1_ctrl(value);
  mmc1_register_write_retry(MMC1_CTRL, value);
  _MMC1_CTRL = value;
}

void split_mmc1_ctrl(char value) {
  DISABLE_IRQ();
  reset_shift_register();
  mmc1_register_write(MMC1_CTRL, value);
  if (_IN_PROGRESS)
    _MMC1_CTRL = value;
  RESTORE_IRQ();
  _IN_PROGRESS = 0;
}

void defer_mmc1_ctrl(char value) { _MMC1_CTRL_NEXT = value & 0b10011; }
