// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Portions originally from cc65.

#ifndef _JOYSTICK_H
#define _JOYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#define JOY_UP_MASK             0x080
#define JOY_DOWN_MASK           0x040
#define JOY_LEFT_MASK           0x020
#define JOY_RIGHT_MASK          0x010
#define JOY_BTN_OPT1_MASK       0x008
#define JOY_BTN_OPT2_MASK       0x004
#define JOY_BTN_B_MASK          0x002
#define JOY_BTN_A_MASK          0x001
#define JOY_BTN_PAUSE_MASK      0x100

// Macros that evaluate the return code of lynx_joy_read
#define JOY_UP(v)              ((v) & JOY_UP_MASK)
#define JOY_DOWN(v)            ((v) & JOY_DOWN_MASK)
#define JOY_LEFT(v)            ((v) & JOY_LEFT_MASK)
#define JOY_RIGHT(v)           ((v) & JOY_RIGHT_MASK)
#define JOY_BTN_A(v)           ((v) & JOY_BTN_A_MASK)
#define JOY_BTN_B(v)           ((v) & JOY_BTN_B_MASK)
#define JOY_BTN_OPT1(v)        ((v) & JOY_BTN_OPT1_MASK)
#define JOY_BTN_OPT2(v)        ((v) & JOY_BTN_OPT2_MASK)
#define JOY_BTN_PAUSE(v)       ((v) & JOY_BTN_PAUSE_MASK)
#define JOY_BTN_RESTART(v)     (((v) & (JOY_BTN_PAUSE_MASK | JOY_BTN_OPT1_MASK)) == (JOY_BTN_PAUSE_MASK | JOY_BTN_OPT1_MASK))
#define JOY_BTN_FLIP(v)        (((v) & (JOY_BTN_PAUSE_MASK | JOY_BTN_OPT2_MASK)) == (JOY_BTN_PAUSE_MASK | JOY_BTN_OPT2_MASK))

// read the current value of all inputs
unsigned short lynx_joy_read();

#ifdef __cplusplus
}
#endif

#endif
