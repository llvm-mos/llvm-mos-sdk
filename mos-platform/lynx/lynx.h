// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

#ifndef _LYNX_H
#define _LYNX_H

#include "audio.h"
#include "cart.h"
#include "clock.h"
#include "eeprom.h"
#include "joystick.h"
#include "video.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Allow #pragma in a macro */
#define DO_PRAGMA(x) _Pragma(#x)

/* Color definitions */
#define COLOR_TRANSPARENT       0x00
#define COLOR_BLACK             0x01
#define COLOR_RED               0x02
#define COLOR_PINK              0x03
#define COLOR_LIGHTGREY         0x04
#define COLOR_GREY              0x05
#define COLOR_DARKGREY          0x06
#define COLOR_BROWN             0x07
#define COLOR_PEACH             0x08
#define COLOR_YELLOW            0x09
#define COLOR_LIGHTGREEN        0x0A
#define COLOR_GREEN             0x0B
#define COLOR_PURPLE            0x0C
#define COLOR_BLUE              0x0D
#define COLOR_LIGHTBLUE         0x0E
#define COLOR_WHITE             0x0F

/* Define Hardware */
#include <mikey.h>
#define MIKEY (*(volatile struct __mikey *)0xFD00)

#define _MIKEY_TIMERS (*(volatile struct _mikey_all_timers *) 0xFD00)  // mikey_timers[8]
#define _HBL_TIMER (*(volatile struct _mikey_timer *) 0xFD00)          // timer0 (HBL)
#define _VBL_TIMER (*(volatile struct _mikey_timer *) 0xFD08)          // timer2 (VBL)
#define _UART_TIMER (*(volatile struct _mikey_timer *) 0xFD14)         // timer4 (UART)
#define _VIDDMA (*(volatile unsigned int *) 0xFD92)                    // dispctl/viddma

#include <suzy.h>
#define SUZY        (*(volatile struct __suzy*)0xFC00)

#define BLOCKSIZE_128K  0x200
#define BLOCKSIZE_256K  0x400
#define BLOCKSIZE_512K  0x800

#define _SET_CART_INFO_IMPL(b0, name, mfr, version, rotation) \
    asm(".global __BLOCKSIZE__ \n __BLOCKSIZE__ = " #b0); \
    asm(".global __VERSION__ \n __VERSION__ = " #version); \
    asm(".global __ROTATION__ \n __ROTATION__ = " #rotation); \
    asm(".global __cartend \n .global __cartmfr \n .global __cartname"); \
    asm(".section .cartnamemfr,\"a\" \n __cartname: \n .asciz " #name " \n __cartmfr: \n .asciz " #mfr " \n __cartend:")

#define SET_CART_INFO(b0, name, mfr, version, rotation) \
    _SET_CART_INFO_IMPL(b0, name, mfr, version, rotation);

#define START_SEGMENT(n) DO_PRAGMA(clang section \
	text=".segment" #n ".text" \
	data=".segment" #n ".data" \
	bss=".segment" #n ".bss" \
	rodata=".segment" #n ".rodata")

#define START_SEGMENT_AT(n, addr) \
	START_SEGMENT(n); \
	asm(".global __SEGMENTSTART" #n "__ \n" "__SEGMENTSTART" #n "__ = " #addr);

#ifdef __cplusplus
}
#endif

#endif
