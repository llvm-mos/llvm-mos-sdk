// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

// clang-format off

/*****************************************************************************/
/*                                                                           */
/*                                  c128.h                                   */
/*                                                                           */
/*                     C128 system specific definitions                      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 1998-2013, Ullrich von Bassewitz                                      */
/*                Roemerstrasse 52                                           */
/*                D-70794 Filderstadt                                        */
/* EMail:         uz@cc65.org                                                */
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



#ifndef _C128_H
#define _C128_H



/* Check for errors */
#if !defined(__C128__)
#  error This module may only be used when compiling for the C128!
#endif



/* Additional key defines */
#define CH_F1                   133
#define CH_F2                   137
#define CH_F3                   134
#define CH_F4                   138
#define CH_F5                   135
#define CH_F6                   139
#define CH_F7                   136
#define CH_F8                   140

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
#define JOY_UP_MASK             0x01
#define JOY_DOWN_MASK           0x02
#define JOY_LEFT_MASK           0x04
#define JOY_RIGHT_MASK          0x08
#define JOY_BTN_1_MASK          0x10

/* Video mode defines */
#define VIDEOMODE_40x25         0x00
#define VIDEOMODE_80x25         0x80
#define VIDEOMODE_40COL         VIDEOMODE_40x25
#define VIDEOMODE_80COL         VIDEOMODE_80x25



/* Define hardware */
#include <_vic2.h>
#define VIC     (*(volatile struct __vic2*)0xD000)

#include <_sid.h>
#define SID     (*(volatile struct __sid*)0xD400)

#include <_vdc.h>
#define VDC     (*(volatile struct __vdc*)0xD600)

#include <_6526.h>
#define CIA1    (*(volatile struct __6526*)0xDC00)
#define CIA2    (*(volatile struct __6526*)0xDD00)



/* Define special memory areas */
#define COLOR_RAM       ((volatile unsigned char*)0xD800)



/**
 * @brief Set the video mode, return the old mode.
 * 
 * @param mode The video mode. Use one of the VIDEOMODE_xx constants.
 * @return unsigned char The old mode.
 */
unsigned char videomode (unsigned char mode);

/**
 * @brief Switch the C128 into C64 mode. Note: This function will not return!
 */
 __attribute__((noreturn))
void c64mode (void);

/**
 * @brief Switch the CPU into 2MHz mode. Note: This will disable video when in
 * 40 column mode.
 */
void fast (void);

/**
 * @brief Switch the CPU into 1MHz mode.
 */
void slow (void);

/**
 * @brief Check CPU clock mode.
 * 
 * @return unsigned char 1 if the CPU is in 2MHz mode.
 */
unsigned char isfast (void);

/* End of c128.h */
#endif
