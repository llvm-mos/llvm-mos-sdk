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
#ifndef _MEGA65_H
#define _MEGA65_H

#ifdef __cplusplus
extern "C" {
#endif

/// @file
/// MEGA65 Registers and Constants
#ifndef __MEGA65__
#error This module may only be used when compiling for the C64!
#endif
#include <_mos4569.h>
#include <_mos6526.h>
#include <_mos6569.h>
#include <_mos6581.h>
#include <mega65-f018.h>
#include <mega65-hypervisor.h>
#include <mega65-math.h>
#include <mega65-viciv.h>
#include <stdint.h>

/// I/O Personality selection
#define IO_KEY (*(volatile char*)0xd02f)
/// C65 Banking Register
#define IO_BANK (*(volatile char*)0xd030)
/// Map 2nd KB of colour RAM $DC00-$DFFF (hiding CIA's)
#define CRAM2K 0b00000001

/// Processor port data direction register
#define PROCPORT_DDR (*(volatile char*)0x00)
/// Mask for PROCESSOR_PORT_DDR which allows only memory configuration to be written
#define PROCPORT_DDR_MEMORY_MASK 0b00000111
/// Processor Port Register controlling RAM/ROM configuration and the datasette
#define PROCPORT (*(volatile char*)0x01)
/// RAM in all three areas 0xA000, 0xD000, 0xE000
#define PROCPORT_RAM_ALL         0b00000000
/// RAM in 0xA000, 0xE000 I/O in 0xD000
#define PROCPORT_RAM_IO          0b00000101
/// RAM in 0xA000, 0xE000 CHAR ROM in 0xD000
#define PROCPORT_RAM_CHARROM     0b00000001
/// RAM in 0xA000, I/O in 0xD000, KERNEL in 0xE000
#define PROCPORT_KERNEL_IO       0b00000110
/// BASIC in 0xA000, I/O in 0xD000, KERNEL in 0xE000
#define PROCPORT_BASIC_KERNEL_IO 0b00000111

/// The VIC-II MOS 6567/6569
#define VICII (*(volatile struct MOS6569_VICII*)0xd000)
/// The VIC III MOS 4567/4569
#define VICIII (*(volatile struct MOS4569_VICIII*)0xd000)
/// The VIC IV
#define VICIV (*(volatile struct MEGA65_VICIV*)0xd000)
/// The address of the CHARGEN character set
#define CHARGEN (*(volatile char*)0xd000)
/// Palette RED
#define PALETTE_RED (*(volatile char*)0xd100)
/// Palette GREEN
#define PALETTE_GREEN (*(volatile char*)0xd200)
/// Palette BLUE
#define PALETTE_BLUE (*(volatile char*)0xd300)
/// The SID MOS 6581/8580
#define SID (*(volatile struct MOS6581_SID *)0xd400)
/// DMAgic F018 Controller
#define DMA (*(volatile struct F018_DMAGIC *)0xd700)
/// Color Ram
#define COLORRAM (*(char*)0xd800)

/// Default address of screen character matrix
#ifdef __MEGA65_C64__
    #define DEFAULT_SCREEN (*(volatile char*)0x0400)
#else
    #define DEFAULT_SCREEN (*(volatile char*)0x0800)
#endif

/// The CIA#1: keyboard matrix, joystick #1/#2
#define CIA1 (*(volatile struct MOS6526_CIA *)0xdc00)
/// The CIA#2: Serial bus, RS-232, VIC memory bank
#define CIA2 (*(volatile struct MOS6526_CIA *)0xdd00)
/// CIA#1 Interrupt for reading in ASM
#define CIA1_INTERRUPT (*(volatile char*)0xdc0d)
/// CIA#2 timer A&B as one single 32-bit value
#define CIA2_TIMER_AB (*(volatile uint32_t*)0xdd04)
/// CIA#2 Interrupt for reading in ASM
#define CIA2_INTERRUPT (*(volatile char*)0xdd0d)

/// Pointer to interrupt function
typedef void (*IRQ_TYPE)(void);

/// The vector used when the KERNAL serves IRQ interrupts
#define KERNEL_IRQ (*(volatile IRQ_TYPE*)0x0314)
/// The vector used when the KERNAL serves NMI interrupts
#define KERNEL_NMI (*(volatile IRQ_TYPE*)0x0318)
/// The vector used when the HARDWARE serves IRQ interrupts
#define HARDWARE_IRQ (*(volatile IRQ_TYPE*)0xfffe)

/// The colors of the C64
#define BLACK 0x0
#define WHITE 0x1
#define RED 0x2
#define CYAN 0x3
#define PURPLE 0x4
#define GREEN 0x5
#define BLUE 0x6
#define YELLOW 0x7
#define ORANGE 0x8
#define BROWN 0x9
#define PINK 0xa
#define DARK_GREY 0xb
#define GREY 0xc
#define LIGHT_GREEN 0xd
#define LIGHT_BLUE 0xe
#define LIGHT_GREY 0xf

#ifdef __cplusplus
}
#endif
#endif 
