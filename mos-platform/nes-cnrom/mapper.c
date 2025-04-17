// Copyright 2022, 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <rompoke.h>
#include "mapper.h"

__attribute__((section(".zp.bss"))) volatile char _BANK_NEXT;

__attribute__((leaf)) void set_chr_bank(char value) {
  _BANK_NEXT = value;
  rom_poke_safe(value);
}

__attribute__((leaf)) void swap_chr_bank(char value) {
  _BANK_NEXT = value;
}

__attribute__((leaf)) void split_chr_bank(char value) {
  rom_poke_safe(value);
}

/**
 * Pass _BANK_NEXT to the physical bank value at the start of NMI. This
 * prevents an inconsistency if the NMI is fired between _BANK_NEXT is set
 * and the ROM being written to. Doing so at the *start* of NMI allows using
 * banked_call and the same "switch to new; run code; switch back to old"
 * code pattern inside NMI handlers.
 *
 * TODO: Adapt to C when the AXY caller convention is present, allowing the
 * compiler to optimize unused shadow variables out.
 */
asm(".section .nmi.10,\"ax\",@progbits\n"
	  "lda _BANK_NEXT\n"
	  "tay\n"
	  "sta __rom_poke_table,y\n");
