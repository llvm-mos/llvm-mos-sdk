// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <peekpoke.h>
#include <mapper.h>

__attribute__((section(".zp.bss"))) bank_index_t __current_bank;

void set_current_bank(bank_index_t bank_id) {
  if (bank_id & 0x80) {
    ram_select(bank_id & 0x7f);
  } else {
    bank_select(bank_id);
  }
}

bank_index_t get_current_bank(void) {
  return __current_bank;
}

void bank_select(bank_index_t bank_id) {
  POKE(0x3f, bank_id);
  __current_bank = bank_id;
}

void ram_select(bank_index_t bank_id) {
  POKE(0x3e, bank_id);
  __current_bank = bank_id | 0x80;
}

void xram_write(int offset, unsigned char value) {
  POKE(MAPPER_XRAM_WRITE | offset, value);
}

unsigned char xram_read(int offset) {
  return PEEK(MAPPER_XRAM_READ | offset);
}

__attribute__((callback(2))) void banked_call_rom(bank_index_t bankId,
                                                  void (*method)(void)) {
  bank_index_t previous_bank_id = get_current_bank();
  bank_select(bankId);
  method();
  set_current_bank(previous_bank_id);
}

__attribute__((callback(2))) void banked_call_ram(bank_index_t bankId,
                                                  void (*method)(void)) {
  bank_index_t previous_bank_id = get_current_bank();
  ram_select(bankId);
  method();
  set_current_bank(previous_bank_id);
}

// From Stella 2023 (cartridge auto-detection):
// 3E cart RAM bankswitching is triggered by storing the bank number
// in address 3E using 'STA $3E', ROM bankswitching is triggered by
// storing the bank number in address 3F using 'STA $3F'.
// We expect the latter will be present at least 2 times, since there
// are at least two banks
// https://github.com/stella-emu/stella/blob/d6224a8a6e30b4b323cde86ade2f05f75dcdfbec/src/emucore/CartDetector.cxx#L4
// It also only calls the 3E detection routine on powers-of-two,
// and if it hasn't detected Superchip via repeating bytes.
//
// Now, on Stella 2014 (used by Libretro) it's a bit different:
// uInt8 signature[] = { 0x85, 0x3E, 0xA9, 0x00 };  // STA $3E; LDA #$00
// So we ought to support both...
__attribute__((used, retain, section(".rom0"))) static void _stella_signature_3e() {
  asm("sta $3f");
  asm("sta $3e");
  asm("lda #$00");
  asm("sta $3f");
}
// Javatari.js detects 3E as a fallback for weird ROM sizes...
// 6 KB, 14 KB, 18 KB, etc.
// or if you have [3E] in the filename.
