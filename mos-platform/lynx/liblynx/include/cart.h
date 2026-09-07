// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Portions originally from cc65.

#ifndef _CART_H
#define _CART_H

#ifdef __cplusplus
extern "C" {
#endif

// Load the contents of a directory entry into memory
void lynx_cart_load(unsigned short entry);

// Seek from the start of the cartrige to the specified position
void lynx_cart_seek(unsigned long position);

// Read from current cart position into dest buffer
void lynx_cart_read(void* dest, unsigned short length);

#ifdef __cplusplus
}
#endif

#endif
