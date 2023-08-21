// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from KickC. Modified from original version.

// clang-format off

/*
 * MIT License
 *
 * Copyright (c) 2017 Jesper Gravgaard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _MEGA65_MATH_H
#define _MEGA65_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/// @file
/// MEGA65 CPU MATHS ACCELERATION REGISTERS
///
/// Every MEGA65 contains a combined 32-bit hardware multiplier and divider. This device
/// takes two 32-bit inputs, MULTINA and MULTINB, and simultaneously calculates:
/// • the 64-bit product of MULTINA and MULTINB
/// • the 32-bit whole part of MULTINA / MULTINB
/// • the 32-bit fractional part of MULTINA / MULTINB
/// It is always updating the outputs based on the inputs, so there is no need to take special
/// action when changing the inputs. The multiplier takes 1 cycle to calculate, and the updated result will thus be available immediately.
/// The hardware divider, however, can take up to 16 cycles depending on the particular inputs. Thus programmers should insert a short
/// delay after changing the inputs before reading the output. As this delay is so short, it can be implemented by simply reading the first
/// byte of the result four times consecutively, as the 4th read will occur after the result has settled.

/// $D70F MATH BUSY
/// Bit 7: DIVBUSY
/// Bit 6: MULBUSY
#define MATH_BUSY (*(volatile char *)0xd70f)

/// $D768-$D76F DIVOUT 64-bit output of MULTINA ÷ MULTINB
/// $D768-$D76B DIVOUT FRAC 32-bit output of MULTINA ÷ MULTINB
#define MATH_DIVOUT_FRAC_CHAR0 (*(volatile signed char*)0xd768)
#define MATH_DIVOUT_FRAC_CHAR1 (*(volatile signed char*)0xd769)
#define MATH_DIVOUT_FRAC_CHAR2 (*(volatile signed char*)0xd76a)
#define MATH_DIVOUT_FRAC_CHAR3 (*(volatile signed char*)0xd76b)
#define MATH_DIVOUT_FRAC_INT0  (*(volatile int16_t*)0xd768)
#define MATH_DIVOUT_FRAC_INT1  (*(volatile int16_t*)0xd76a)
#define MATH_DIVOUT_FRAC_LONG0 (*(volatile int32_t*)0xd768)
/// $D768-$D76F DIVOUT 64-bit output of MULTINA ÷ MULTINB
#define MATH_DIVOUT_WHOLE_CHAR0 (*(volatile signed char*)0xd76c)
#define MATH_DIVOUT_WHOLE_INT0  (*(volatile int16_t*)0xd76c)
#define MATH_DIVOUT_WHOLE_INT1  (*(volatile int16_t*)0xd76e)
#define MATH_DIVOUT_WHOLE_LONG  (*(volatile int32_t*)0xd76c)

/// $D770-$D773 MULTINA Multiplier input A / Divider numerator (32 bit)
#define MATH_MULTINA_CHAR0 (*(volatile signed char*)0xd770)
#define MATH_MULTINA_CHAR1 (*(volatile signed char*)0xd771)
#define MATH_MULTINA_CHAR2 (*(volatile signed char*)0xd772)
#define MATH_MULTINA_CHAR3 (*(volatile signed char*)0xd773)
#define MATH_MULTINA_INT0  (*(volatile int16_t*)0xd770)
#define MATH_MULTINA_INT1  (*(volatile int16_t*)0xd772)
#define MATH_MULTINA_LONG  (*(volatile int32_t*)0xd770)

/// $D774-$D777 MULTINB Multiplier input B / Divider denominator (32 bit)
#define MATH_MULTINB_CHAR0 (*(volatile signed char*)0xd774)
#define MATH_MULTINB_CHAR1 (*(volatile signed char*)0xd775)
#define MATH_MULTINB_CHAR2 (*(volatile signed char*)0xd776)
#define MATH_MULTINB_CHAR3 (*(volatile signed char*)0xd777)
#define MATH_MULTINB_INT0  (*(volatile int16_t*)0xd774)
#define MATH_MULTINB_INT1  (*(volatile int16_t*)0xd776)
#define MATH_MULTINB_LONG  (*(volatile int32_t*)0xd774)

/// $D778-$D77F MULTOUT 64-bit output of MULTINA × MULTINB
#define MATH_MULTOUT_CHAR0 (*(volatile signed char*)0xd778)
#define MATH_MULTOUT_INT0  (*(volatile int16_t*)0xd778)
#define MATH_MULTOUT_LONG0 (*(volatile int32_t*)0xd778)
#define MATH_MULTOUT_LONG1 (*(volatile int32_t*)0xd77c)

#ifdef __cplusplus
}
#endif
#endif 
