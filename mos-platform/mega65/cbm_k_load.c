// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// MEGA65 override of commodore cbm_k_load. Delegates to mega65_k_load(),
// which restores Z after the KERNAL call.

#include <mega65.h>

// Load or verify a file (LOAD, $FFD5).
// Requires cbm_k_setlfs() and cbm_k_setnam() called first.
// On MEGA65, also call mega65_k_setbnk() to set the data/filename banks.
// @param flag       0=load, 1=verify.
// @param load_addr  Destination address (used when SA=0).
// @return Pointer past the last byte loaded, or error code as pointer.
void *cbm_k_load(const uint8_t flag, void *load_addr) {
  void *end_addr;
  uint8_t err = mega65_k_load(flag, load_addr, &end_addr);
  // end_addr is only written on success, so the error has to be what comes
  // back otherwise -- as a pointer, matching the commodore version.
  return err ? (void *)(uint16_t)err : end_addr;
}
