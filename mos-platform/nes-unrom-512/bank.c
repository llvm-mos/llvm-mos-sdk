// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "bank.h"

extern char _BANK;
__attribute__((section(".zp.bss"))) char _BANK_SHADOW;

__attribute__((leaf)) inline char get_bank_state(char mask) {
  return _BANK_SHADOW & mask;
}

__attribute__((leaf)) inline char set_bank_state(char mask, char value) {
  char old = _BANK_SHADOW;
  _BANK = (_BANK_SHADOW = (old & (~mask)) | value);
  return old;
}

__attribute__((leaf)) char get_prg_bank(void) {
  return get_bank_state(UNROM_512_PRG_BANK_MASK);
}

__attribute__((leaf)) char set_prg_bank(char value) {
  return set_bank_state(UNROM_512_PRG_BANK_MASK, value);
}

__attribute__((leaf)) inline char get_chr_bank(void) {
  return get_bank_state(UNROM_512_CHR_BANK_MASK) >> UNROM_512_CHR_BANK_SHIFT;
}

__attribute__((leaf)) inline char set_chr_bank(char bank_id) {
  return set_bank_state(UNROM_512_CHR_BANK_MASK, bank_id << UNROM_512_CHR_BANK_SHIFT);
}

__attribute__((leaf)) inline char get_mirrored_screen(void) {
  return get_bank_state(UNROM_512_MIRROR_SCREEN_MASK) >> UNROM_512_MIRROR_SCREEN_SHIFT;
}

__attribute__((leaf)) inline char set_mirrored_screen(char screen_id) {
  return set_bank_state(UNROM_512_MIRROR_SCREEN_MASK, screen_id << UNROM_512_MIRROR_SCREEN_SHIFT);
}

