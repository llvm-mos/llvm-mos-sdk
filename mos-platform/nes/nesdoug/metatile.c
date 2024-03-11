// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Keeping these functions in C LTOs them in, which informs LTO code generation
// that the ZP regions aren't available. This saves users of the library from
// having to manually reserve ZP space from LTO.
__attribute__((section(".zp.meta_ptr"))) const char *META_PTR;
__attribute__((section(".zp.data_ptr"))) const char *DATA_PTR;

void set_data_pointer(const void *data) { DATA_PTR = (const char *)data; }
void set_mt_pointer(const void *metatiles) {
  META_PTR = (const char *)metatiles;
}
