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
#include <stdbool.h>

// Always bring in the NMI handler
asm(".globl bank_nmi");

__attribute__((section(".zp.bss"))) volatile char _CHR_BANK0_NEXT;
__attribute__((section(".zp.bss"))) volatile char _CHR_BANK1_NEXT;
__attribute__((section(".zp.data"))) volatile char _MMC1_CTRL_NEXT =
    CHR_BANK_MODE_4 | MIRROR_VERTICAL;

__attribute__((section(".zp.bss"))) volatile char _PRG_BANK;
__attribute__((section(".zp.bss"))) volatile char _CHR_BANK0;
__attribute__((section(".zp.bss"))) volatile char _CHR_BANK1;
__attribute__((section(".zp.data"))) volatile char _MMC1_CTRL =
    PRG_ROM_BANK_MODE_FIXED_C000;
__attribute__((section(".zp.bss"))) volatile bool _IN_PROGRESS;

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

// Reliably set the given register with the given shadow to (current & cur_mask
// | val).
__attribute__((always_inline)) static inline void
set_register_bits(unsigned addr, volatile char *shadow, char cur_mask,
                  char val) {
  DISABLE_IRQ();
  char new = *shadow &cur_mask | val;
  // Setting this afterwards would instead create the possibility
  // that the NMI could occur between successful finish of the write and
  // updating the shadow; in that case, the shadow would be wrong. Instead,
  // this is set preemptively, and the NMI handler summarily flushes shadow
  // registers, which makes state consistent on entry.
  *shadow = new;
  _IN_PROGRESS = true;
  mmc1_register_write(addr, new);
  while (!_IN_PROGRESS) {
    _IN_PROGRESS = true;
    // The write was interrupted by the NMI. The NMI is guaranteed to reset the
    // shift register and perform full writes, after which some unknown number
    // of writes were performed by this routine. Part of the NMI is flushing all
    // shadow registers, and reliable (PRG) register state is callee-saved WRT
    // NMI, so the write is complete. Accordingly, we just need to reset the
    // shift register. This clobbers MMC1_CTRL, so flush its shadow afterwards.
    // Do this in a loop until not interrupted by new NMIs (paranoid, but
    // inexpensive).
    reset_shift_register();
    mmc1_register_write(MMC1_CTRL, _MMC1_CTRL);
  }
  _IN_PROGRESS = false;
  RESTORE_IRQ();
}

char get_prg_bank(void) { return _PRG_BANK; }
__attribute__((alias("get_prg_bank"))) char __get_prg_bank(void);

void set_prg_bank(char bank_id) {
  set_register_bits(MMC1_PRG, &_PRG_BANK, 0xff, bank_id);
}
__attribute__((alias("set_prg_bank"))) void __set_prg_bank(char);

void set_chr_bank_0(char bank_id) {
  defer_chr_bank_0(bank_id);
  split_chr_bank_0(bank_id);
}

void set_chr_bank_1(char bank_id) {
  defer_chr_bank_1(bank_id);
  split_chr_bank_1(bank_id);
}

void split_chr_bank_0(char bank_id) {
  set_register_bits(MMC1_CHR0, &_CHR_BANK0, 0xff, bank_id);
}

void defer_chr_bank_0(char bank_id) { _CHR_BANK0_NEXT = bank_id; }

void defer_chr_bank_1(char bank_id) { _CHR_BANK1_NEXT = bank_id; }

void split_chr_bank_1(char bank_id) {
  set_register_bits(MMC1_CHR1, &_CHR_BANK1, 0xff, bank_id);
}

extern char __chr_high_mask[];
extern char __chr_low_mask[];

char get_chr_bank_0_high(void) { return _CHR_BANK0 & (char)(__chr_high_mask); }

void set_chr_bank_0_high(char bank_id) {
  set_register_bits(MMC1_CHR0, &_CHR_BANK0, (char)(__chr_low_mask), bank_id);
}

char get_chr_bank_1_high(void) { return _CHR_BANK1 & (char)(__chr_high_mask); }

void set_chr_bank_1_high(char bank_id) {
  set_register_bits(MMC1_CHR1, &_CHR_BANK1, (char)(__chr_low_mask), bank_id);
}

void set_mirroring(enum Mirroring mirroring) {
  defer_mirroring(mirroring);
  split_mirroring(mirroring);
}

void split_mirroring(enum Mirroring mirroring) {
  set_register_bits(MMC1_CTRL, &_MMC1_CTRL, 0b11100, mirroring);
}

void defer_mirroring(enum Mirroring mirroring) {
  _MMC1_CTRL_NEXT = _MMC1_CTRL_NEXT & 0b01111 | mirroring;
}

void set_chr_bank_mode(enum ChrBankMode mode) {
  defer_chr_bank_mode(mode);
  split_chr_bank_mode(mode);
}

void split_chr_bank_mode(enum ChrBankMode mode) {
  set_register_bits(MMC1_CTRL, &_MMC1_CTRL, 0b01111, mode);
}

void defer_chr_bank_mode(enum ChrBankMode mode) {
  _MMC1_CTRL_NEXT = _MMC1_CTRL_NEXT & 0b11100 | mode;
}

void set_prg_rom_bank_mode(enum PrgRomBankMode mode) {
  set_register_bits(MMC1_CTRL, &_MMC1_CTRL, 0b10011, mode);
}

enum PrgRomBankMode get_prg_rom_bank_mode(void) { return _MMC1_CTRL & 0b01100; }

void set_mmc1_ctrl(char value) {
  defer_mmc1_ctrl(value);
  split_mmc1_ctrl(value);
}

void split_mmc1_ctrl(char value) {
  set_register_bits(MMC1_CTRL, &_MMC1_CTRL, 0xff, value);
}

void defer_mmc1_ctrl(char value) { _MMC1_CTRL_NEXT = value & 0b10011; }
