// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

// clang-format off

/*****************************************************************************/
/*                                                                           */
/*                                  lynx.h                                   */
/*                                                                           */
/*                     Lynx system-specific definitions                      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2003      Shawn Jefferson                                             */
/*                                                                           */
/* Adapted with many changes Ullrich von Bassewitz, 2004-10-09               */
/*                                                                           */
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

#ifndef _LYNX_H
#define _LYNX_H

/* Check for errors */
#if !defined(__LYNX__)
#  error This module may only be used when compiling for the Lynx game console!
#endif

/* Masks for joy_read */
#define JOY_UP_MASK             0x80
#define JOY_DOWN_MASK           0x40
#define JOY_LEFT_MASK           0x20
#define JOY_RIGHT_MASK          0x10
#define JOY_BTN_1_MASK          0x01
#define JOY_BTN_2_MASK          0x02

#define JOY_BTN_A_MASK          JOY_BTN_1_MASK
#define JOY_BTN_B_MASK          JOY_BTN_2_MASK

#define JOY_BTN_A(v)            ((v) & JOY_BTN_A_MASK)
#define JOY_BTN_B(v)            ((v) & JOY_BTN_B_MASK)

/* Define Hardware */
#include <_mikey.h>
#define MIKEY (*(volatile struct __mikey *)0xFD00)

#define _MIKEY_TIMERS (*(volatile struct _mikey_all_timers *) 0xFD00)  // mikey_timers[8]
#define _HBL_TIMER (*(volatile struct _mikey_timer *) 0xFD00)          // timer0 (HBL)
#define _VBL_TIMER (*(volatile struct _mikey_timer *) 0xFD08)          // timer2 (VBL)
#define _UART_TIMER (*(volatile struct _mikey_timer *) 0xFD14)         // timer4 (UART)
#define _VIDDMA (*(volatile unsigned int *) 0xFD92)                    // dispctl/viddma

#include <_suzy.h>
#define SUZY        (*(volatile struct __suzy*)0xFC00)

/* End of lynx.h */
#endif
