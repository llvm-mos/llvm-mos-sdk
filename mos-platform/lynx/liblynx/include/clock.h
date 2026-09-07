// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Portions originally from cc65.

#ifndef _CLOCK_H
#define _CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

void lynx_clock_init();
unsigned long lynx_clock_getticks();


#ifdef __cplusplus
}
#endif

#endif
