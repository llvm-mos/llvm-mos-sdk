// Copyright 2022, 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <rompoke.h>
#include "bank.h"

__attribute__((section(".zp.bss"))) char _BANK_SHADOW;

__attribute__((leaf)) char get_chr_bank(void) {
  return _BANK_SHADOW;
}

__attribute__((leaf)) void set_chr_bank(char value) {
  rom_poke_safe(_BANK_SHADOW = value);
}
