// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <rompoke.h>
#include "mapper.h"

#define _BANK (*(volatile char*)0x5000)
/**
 * @brief Shadow variable for the currently set bank state.
 */
__attribute__((section(".zp.bss"))) volatile char _BANK_NEXT;
/**
 * @brief Shadow variable for the CHR/mirroring bank state 
 * to be set at next NMI.
 */
volatile char _CHR_NMI_BANK_NEXT;

__attribute__((leaf)) inline char get_bank_state(void) {
  return _BANK_NEXT;
}

__attribute__((leaf)) inline char set_bank_state(char value) {
  char old = _BANK_NEXT;
  _BANK_NEXT = value;
  _BANK = value;
  return old;
}

__attribute__((leaf)) static inline char get_bank_bits(char mask) {
  return _BANK_NEXT & mask;
}

__attribute__((leaf)) static inline char set_prg_bank_bits(char mask, char value) {
  char old = _BANK_NEXT;
  char new = (old & (~mask)) | value;
  _BANK_NEXT = new;
  _BANK = new;
  return old;
}

__attribute__((leaf)) static inline void swap_chr_bank_bits(char mask, char value) {
  char old = _CHR_NMI_BANK_NEXT;
  _CHR_NMI_BANK_NEXT = (old & (~mask)) | value;
}

// Both set _BANK_NEXT and write to ROM without using _CHR_NMI_BANK_NEXT.
#define split_chr_bank_bits set_prg_bank_bits

__attribute__((leaf)) static inline void set_chr_bank_bits(char mask, char value) {
  // swap
  char old = _CHR_NMI_BANK_NEXT;
  char new_chr = (old & (~mask)) | value;
  _CHR_NMI_BANK_NEXT = new_chr;

  // split
  char current_non_chr = _BANK_NEXT & 0xCF;
  char new = current_non_chr | new_chr;
  _BANK_NEXT = new;
  _BANK = new;
}

__attribute__((leaf)) char get_prg_bank(void) {
  return get_bank_bits(PRG_BANK_MASK);
}

__attribute__((leaf)) char set_prg_bank(char value) {
  return set_prg_bank_bits(PRG_BANK_MASK, value);
}

__attribute__((leaf)) char set_mapper_red_led(bool value) {
  return set_prg_bank_bits(MAPPER_RED_LED, value ? MAPPER_RED_LED : 0);
}

__attribute__((leaf)) char set_mapper_green_led(bool value) {
  return set_prg_bank_bits(MAPPER_GREEN_LED, value ? MAPPER_GREEN_LED : 0);
}

__attribute__((leaf)) inline void set_chr_bank(char bank_id) {
  set_chr_bank_bits(CHR_BANK_MASK, bank_id ? CHR_BANK_1 : CHR_BANK_0);
}

__attribute__((leaf)) inline void swap_chr_bank(char bank_id) {
  swap_chr_bank_bits(CHR_BANK_MASK, bank_id ? CHR_BANK_1 : CHR_BANK_0);
}

__attribute__((leaf)) inline void split_chr_bank(char bank_id) {
  split_chr_bank_bits(CHR_BANK_MASK, bank_id ? CHR_BANK_1 : CHR_BANK_0);
}

__attribute__((leaf)) inline void set_nt_bank(char bank_id) {
  set_chr_bank_bits(NT_BANK_MASK, bank_id ? NT_BANK_1 : NT_BANK_0);
}

__attribute__((leaf)) inline void swap_nt_bank(char bank_id) {
  swap_chr_bank_bits(NT_BANK_MASK, bank_id ? NT_BANK_1 : NT_BANK_0);
}

__attribute__((leaf)) inline void split_nt_bank(char bank_id) {
  split_chr_bank_bits(NT_BANK_MASK, bank_id ? NT_BANK_1 : NT_BANK_0);
}

/**
 * Pass _BANK_NEXT to the physical bank value at the start of NMI. This
 * prevents an inconsistency if the NMI is fired between _BANK_NEXT is set
 * and the ROM being written to. Doing so at the *start* of NMI allows using
 * banked_call and the same "switch to new; run code; switch back to old"
 * code pattern inside NMI handlers.
 *
 * To handle CHR-ROM, _CHR_NMI_BANK_NEXT is OR'd with the masked value of
 * _BANK_NEXT, then written back to _BANK_NEXT. This allows handling all
 * inconsistency options:
 *
 * store _CHR_NMI_BANK_NEXT
 * <- NMI writes value to _BANK_NEXT, then to the mapper register
 * store _BANK_NEXT
 * <- NMI writes value to the mapper register
 * store mapper register
 */
asm(".section .nmi.10,\"ax\",@progbits\n"
    "lda _BANK_NEXT\n"
    "and #$CF\n"
    "ora _CHR_NMI_BANK_NEXT\n"
    "sta _BANK_NEXT\n"
    "sta $5000\n");
