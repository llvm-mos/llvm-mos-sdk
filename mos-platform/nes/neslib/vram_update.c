// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

__attribute__((section(".zp.name_upd_adr"))) volatile const char *NAME_UPD_ADR;
__attribute__((section(".zp.name_upd_enable"))) volatile char NAME_UPD_ENABLE;

void set_vram_update(const void *buf) {
  NAME_UPD_ADR = buf;
  NAME_UPD_ENABLE = NAME_UPD_ADR != 0;
}

// Bring in assembly module
asm (".globl vram_update_nmi");
