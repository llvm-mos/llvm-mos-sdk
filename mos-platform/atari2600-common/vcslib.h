// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _VCSLIB_H
#define _VCSLIB_H

#include <atari2600.h>
#include <stdint.h>

#if defined(__ATARI2600_MAPPER__)
#include <mapper.h>
#endif

// Define data types for different data sizes and signedness

typedef unsigned char byte;   // 8-bit unsigned data type
typedef signed char sbyte;    // 8-bit signed data type
typedef unsigned short word;  // 16-bit unsigned data type

// Atari 2600 kernel helpers, called in a sequence every frame

void kernel_1(void);	// before preframe
void kernel_2(void);	// before kernel
void kernel_3(void);	// after kernel
void kernel_4(void);	// after postframe

// Function to set horizontal position of a game object.

typedef enum { PLAYER_0=0, PLAYER_1, MISSILE_0, MISSILE_1, BALL } TIAObject;

// A = X coordinate
// X = object index
void _set_horiz_pos(byte xpos, byte objindex);

// swap order of call
#define set_horiz_pos(objindex,xpos) _set_horiz_pos(xpos,objindex)

// Waits for next scanline start
#define do_wsync() \
        asm("sta $42 /* WSYNC */");

// Applies horizontal motion to sprite(s) after set_horiz_pos()
#define apply_hmove() \
        asm("sta $42 /* WSYNC */" "\n" "sta $6a /* HMOVE */");

// Macros

#define P0	0
#define P1	1
#define M0	2
#define M1	3
#define BALL	4

#define SW_RESET()	((RIOT.swchb & RESET_MASK) == 0)
#define SW_SELECT()	((RIOT.swchb & SELECT_MASK) == 0)
#define SW_COLOR()	((RIOT.swchb & BW_MASK) != 0)
#define SW_P0_PRO()	((RIOT.swchb & P0_DIFF_MASK) != 0)
#define SW_P1_PRO()	((RIOT.swchb & P1_DIFF_MASK) != 0)

#define JOY_UP(plyr)    (!(RIOT.swcha & ((plyr) ? 0x1 : ~MOVE_UP)))
#define JOY_DOWN(plyr)  (!(RIOT.swcha & ((plyr) ? 0x2 : ~MOVE_DOWN)))
#define JOY_LEFT(plyr)  (!(RIOT.swcha & ((plyr) ? 0x4 : ~MOVE_LEFT)))
#define JOY_RIGHT(plyr) (!(RIOT.swcha & ((plyr) ? 0x8 : ~MOVE_RIGHT)))
#define JOY_FIRE(plyr)  !(((plyr) ? TIA.inpt5 : TIA.inpt4) & 0x80)

// make color greyscale if black and white switch is set
#define COLOR_CONV(color) (SW_COLOR() ? color : color & 0x0f)

// macros for setting PIA timers
#define _CYCLES(lines) (((lines) * 76) - 13)
#define _TIM64(cycles) (((cycles) >> 6) - (((cycles) & 63) < 12))
#define _T1024(cycles) ((cycles) >> 10)

#ifdef PAL
#define VBLANK_TIM64 _TIM64(_CYCLES(45))
#define KERNAL_T1024 _T1024(_CYCLES(250))
#define OVERSCAN_TIM64 _TIM64(_CYCLES(36))
#else
#define VBLANK_TIM64 _TIM64(_CYCLES(37))
#define KERNAL_TIM64 _TIM64(_CYCLES(194))
#define OVERSCAN_TIM64 _TIM64(_CYCLES(32))
#endif

#endif
