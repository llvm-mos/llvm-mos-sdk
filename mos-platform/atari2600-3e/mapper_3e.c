// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "peekpoke.h"
#include "mapper.h"

__attribute__((section(".zp.bss"))) bank_index_t __current_bank;

__attribute__((weak)) void set_current_bank(bank_index_t bank_id) {
  if (bank_select && !(bank_id & 0x80)) {
    bank_select(bank_id);
  } else if (ram_select) {
    ram_select(bank_id & 0x7f);
  }
}

__attribute__((always_inline, leaf)) bank_index_t get_current_bank(void) {
  return __current_bank;
}

__attribute__((leaf)) void bank_select(bank_index_t bank_id) {
  POKE(0x3f, bank_id);
  __current_bank = bank_id;
}

__attribute__((leaf)) void ram_select(bank_index_t bank_id) {
  POKE(0x3e, bank_id);
  __current_bank = bank_id | 0x80;
}

__attribute__((leaf)) void xram_write(int address, unsigned char value) {
  POKE(0x1400 + address, value);
}

__attribute__((leaf)) unsigned char xram_read(int address) {
  return PEEK(0x1000 + address);
}

__attribute__((weak, callback(2))) void banked_call_rom(bank_index_t bankId,
                                                        void (*method)(void)) {
  bank_index_t previous_bank_id = get_current_bank();
  bank_select(bankId);
  method();
  set_current_bank(previous_bank_id);
}

__attribute__((weak, callback(2))) void banked_call_ram(bank_index_t bankId,
                                                        void (*method)(void)) {
  bank_index_t previous_bank_id = get_current_bank();
  ram_select(bankId);
  method();
  set_current_bank(previous_bank_id);
}

