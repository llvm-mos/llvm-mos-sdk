// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

extern volatile char __rom_poke_table[];

__attribute__((leaf)) void rom_poke_safe(char value) {
    __rom_poke_table[value] = value;
}
