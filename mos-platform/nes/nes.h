// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modififed from original version.

/*****************************************************************************/
/*                                                                           */
/*                                   nes.h                                   */
/*                                                                           */
/*                      NES system specific definitions                      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2002-2003 Groepaz/Hitmen                                              */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



#ifndef _NES_H
#define _NES_H



/* Check for errors */
#if !defined(__NES__)
#  error This module may only be used when compiling for the NES!
#endif



/* Color defines */
#define COLOR_BLACK             0x00
#define COLOR_WHITE             0x01
#define COLOR_RED               0x02
#define COLOR_CYAN              0x03
#define COLOR_PURPLE            0x04
#define COLOR_GREEN             0x05
#define COLOR_BLUE              0x06
#define COLOR_YELLOW            0x07
#define COLOR_ORANGE            0x08
#define COLOR_BROWN             0x09
#define COLOR_LIGHTRED          0x0A
#define COLOR_GRAY1             0x0B
#define COLOR_GRAY2             0x0C
#define COLOR_LIGHTGREEN        0x0D
#define COLOR_LIGHTBLUE         0x0E
#define COLOR_GRAY3             0x0F

/* Masks for joy_read */
#define JOY_UP_MASK     0x10
#define JOY_DOWN_MASK   0x20
#define JOY_LEFT_MASK   0x40
#define JOY_RIGHT_MASK  0x80
#define JOY_BTN_1_MASK  0x01
#define JOY_BTN_2_MASK  0x02
#define JOY_BTN_3_MASK  0x04
#define JOY_BTN_4_MASK  0x08

#define JOY_BTN_A_MASK  JOY_BTN_1_MASK
#define JOY_BTN_B_MASK  JOY_BTN_2_MASK
#define JOY_SELECT_MASK JOY_BTN_3_MASK
#define JOY_START_MASK  JOY_BTN_4_MASK

#define JOY_BTN_A(v)    ((v) & JOY_BTN_A_MASK)
#define JOY_BTN_B(v)    ((v) & JOY_BTN_B_MASK)
#define JOY_SELECT(v)   ((v) & JOY_SELECT_MASK)
#define JOY_START(v)    ((v) & JOY_START_MASK)

/* Return codes of get_tv */
#define TV_NTSC         0
#define TV_PAL          1
#define TV_OTHER        2

/* Define hardware */

/* Picture Processing Unit */
struct __ppu {
    unsigned char control;
    unsigned char mask;                 /* color; show sprites, background */
    char const status;
    struct {
        unsigned char address;
        unsigned char data;
    } sprite;
    unsigned char scroll;
    struct {
        unsigned char address;
        unsigned char data;
    } vram;
};
#define PPU             (*(volatile struct __ppu*)0x2000)
#define SPRITE_DMA      (APU.sprite.dma)

/* Audio Processing Unit */
struct __apu {
    struct {
        unsigned char control;          /* duty, counter halt, volume/envelope */
        unsigned char ramp;
        unsigned char period_low;       /* timing */
        unsigned char len_period_high;  /* length, timing */
    } pulse[2];
    struct {
        unsigned char counter;          /* counter halt, linear counter */
        unsigned char unused;
        unsigned char period_low;       /* timing */
        unsigned char len_period_high;  /* length, timing */
    } triangle;
    struct {
        unsigned char control;          /* counter halt, volume/envelope */
        unsigned char unused;
        unsigned char period;           /* loop, timing */
        unsigned char len;              /* length */
    } noise;
    struct {
        unsigned char control;          /* IRQ, loop, rate */
        unsigned char output;           /* output value */
        unsigned char address;
        unsigned char length;
    } delta_mod;                        /* delta pulse-code modulation */
    struct {
        unsigned char dma;
    } sprite;
    char status;
    unsigned char unused;
    unsigned char fcontrol;
};
#define APU             (*(volatile struct __apu*)0x4000)

#define JOYPAD          ((unsigned char volatile[2])0x4016)

// TODO
#if 0
void waitvsync (void);
/* Wait for start of the next frame */

unsigned char get_tv (void);
/* Return the video mode the machine is using. */
#endif



/* End of nes.h */
#endif
