// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <rompoke.h>
#include "mapper.h"

/**
 * @brief Shadow variable for the currently set bank state.
 */
__attribute__((section(".zp.bss"))) volatile char _BANK_SHADOW;
/**
 * @brief Shadow variable for the CHR/mirroring bank state 
 * to be set at next NMI.
 */
volatile char _CHR_BANK_NMI_NEXT;

__attribute__((leaf)) inline char get_bank_state(void) {
  return _BANK_SHADOW;
}

__attribute__((leaf)) inline char set_bank_state(char value) {
  char old = _BANK_SHADOW;
  _BANK_SHADOW = value;
  rom_poke_safe(value);
  return old;
}

__attribute__((leaf)) static inline char get_bank_bits(char mask) {
  return _BANK_SHADOW & mask;
}

__attribute__((leaf)) static inline char set_prg_bank_bits(char mask, char value) {
  char old = _BANK_SHADOW;
  char new = (old & (~mask)) | value;
  _BANK_SHADOW = new;
  rom_poke_safe(new);
  return old;
}

__attribute__((leaf)) static inline void swap_chr_bank_bits(char mask, char value) {
  char old = _CHR_BANK_NMI_NEXT;
  _CHR_BANK_NMI_NEXT = (old & (~mask)) | value;
}

// Both set _BANK_SHADOW and write to ROM without using _CHR_BANK_NMI_NEXT.
#define split_chr_bank_bits set_prg_bank_bits

__attribute__((leaf)) static inline void set_chr_bank_bits(char mask, char value) {
  // swap
  char old = _CHR_BANK_NMI_NEXT;
  char new_chr = (old & (~mask)) | value;
  _CHR_BANK_NMI_NEXT = new_chr;

  // split
  char current_non_chr = _BANK_SHADOW & 0x1F;
  char new = current_non_chr | new_chr;
  _BANK_SHADOW = new;
  rom_poke_safe(new);
}

__attribute__((leaf)) char get_prg_bank(void) {
  return get_bank_bits(PRG_BANK_MASK);
}

__attribute__((leaf)) char set_prg_bank(char value) {
  return set_prg_bank_bits(PRG_BANK_MASK, value);
}

__attribute__((leaf)) inline void set_chr_bank(char bank_id) {
  set_chr_bank_bits(CHR_BANK_MASK, bank_id << CHR_BANK_SHIFT);
}

__attribute__((leaf)) inline void swap_chr_bank(char bank_id) {
  swap_chr_bank_bits(CHR_BANK_MASK, bank_id << CHR_BANK_SHIFT);
}

__attribute__((leaf)) inline void split_chr_bank(char bank_id) {
  split_chr_bank_bits(CHR_BANK_MASK, bank_id << CHR_BANK_SHIFT);
}

__attribute__((leaf)) inline void set_mirrored_screen(char screen_id) {
  set_chr_bank_bits(MIRROR_SCREEN_MASK, screen_id << MIRROR_SCREEN_SHIFT);
}

__attribute__((leaf)) inline void swap_mirrored_screen(char screen_id) {
  swap_chr_bank_bits(MIRROR_SCREEN_MASK, screen_id << MIRROR_SCREEN_SHIFT);
}

__attribute__((leaf)) inline void split_mirrored_screen(char screen_id) {
  split_chr_bank_bits(MIRROR_SCREEN_MASK, screen_id << MIRROR_SCREEN_SHIFT);
}

/**
 * Pass _BANK_SHADOW to the physical bank value at the start of NMI. This
 * prevents an inconsistency if the NMI is fired between _BANK_SHADOW is set
 * and the ROM being written to. Doing so at the *start* of NMI allows using
 * banked_call and the same "switch to new; run code; switch back to old"
 * code pattern inside NMI handlers.
 *
 * To handle CHR-ROM, _CHR_BANK_NMI_NEXT is OR'd with the masked value of
 * _BANK_SHADOW, then written back to _BANK_SHADOW. This allows handling all
 * inconsistency options:
 *
 * store _CHR_BANK_NMI_NEXT
 * <- NMI writes value to _BANK_SHADOW, then to the mapper register
 * store _BANK_SHADOW
 * <- NMI writes value to the mapper register
 * store mapper register
 */
asm(".section .nmi.10,\"ax\",@progbits\n"
    "lda _BANK_SHADOW\n"
    "and #$1F\n"
    "ora _CHR_BANK_NMI_NEXT\n"
    "sta _BANK_SHADOW\n"
    "tay\n"
    "sta __rom_poke_table,y\n");
