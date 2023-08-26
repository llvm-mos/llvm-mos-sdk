// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Partially sourced from KickC and modified from original version;
// original license follows:

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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <_6526.h>
#include <_sid.h>
#include <_vic2.h>
#include <_vic3.h>
#include <_vic4.h>

struct __hypervisor {
  uint8_t htrap[64];
};

/// Registers for the MEGA65 math accelerator
struct __cpu_math {
  union {
    struct {
      uint32_t divout_fract; //!< Fractional part of MULTINA / MULTINB (0xD768)
      uint32_t divout_whole; //!< Whole part of MULTINA / MULTINB (0xD76C)
    };
#ifndef __CC65__
    uint64_t divout; //!< 64-bit result of MULTINA / MULTINB (0xD768)
#endif
  };
  /// 32-bit Multiplier input A (0xD770)
  uint32_t multina;
  /// 32-bit Multiplier input B (0xD774)
  uint32_t multinb;
  /// 64-but product of MULTINA and MULTINB (0xD778)
#ifdef __CC65__
  uint32_t multout_lsb;
  uint32_t multout_msb;
#else
  uint64_t multout;
#endif
  /// 32-bit programmable input (0xD780)
  uint32_t mathin[16];
};
#ifdef __cplusplus
static_assert(sizeof(__cpu_math) == 88);
#endif

/// RGB color palette
struct __color_palette {
  uint8_t red[256];
  uint8_t green[256];
  uint8_t blue[256];
};

/// I/O Personality selection
#define IO_KEY (*(volatile uint8_t *)0xd02f)
/// C65 Banking Register
#define IO_BANK (*(volatile uint8_t *)0xd030)
/// Map 2nd KB of colour RAM $DC00-$DFFF (hiding CIA's)
#define CRAM2K 0b00000001
/// Processor port data direction register
#define PROCPORT_DDR (*(volatile uint8_t *)0x00)
/// Mask for PROCESSOR_PORT_DDR which allows only memory configuration to be
/// written
#define PROCPORT_DDR_MEMORY_MASK 0b00000111
/// Processor Port Register controlling RAM/ROM configuration and the datasette
#define PROCPORT (*(volatile uint8_t *)0x01)
/// RAM in all three areas 0xA000, 0xD000, 0xE000
#define PROCPORT_RAM_ALL 0b00000000
/// RAM in 0xA000, 0xE000 I/O in 0xD000
#define PROCPORT_RAM_IO 0b00000101
/// RAM in 0xA000, 0xE000 CHAR ROM in 0xD000
#define PROCPORT_RAM_CHARROM 0b00000001
/// RAM in 0xA000, I/O in 0xD000, KERNEL in 0xE000
#define PROCPORT_KERNEL_IO 0b00000110
/// BASIC in 0xA000, I/O in 0xD000, KERNEL in 0xE000
#define PROCPORT_BASIC_KERNEL_IO 0b00000111
/// The VIC-II MOS 6567/6569
#define VICII (*(volatile struct __vic2 *)0xd000)
/// The VIC IV
#define VICIV (*(volatile struct __vic4 *)0xd000)
/// The address of the CHARGEN character set
#define CHARGEN (*(volatile uint8_t *)0xd000)
/// Color palette
#define PALETTE (*(volatile struct __color_palette *)0xd100)
/// SID MOS 6581/8580
#define SID1 (*(volatile struct __sid *)0xd400)
/// SID MOS 6581/8580
#define SID2 (*(volatile struct __sid *)0xd420)
/// SID MOS 6581/8580
#define SID3 (*(volatile struct __sid *)0xd440)
/// SID MOS 6581/8580
#define SID4 (*(volatile struct __sid *)0xd460)
/// SID select mode (0=6581, 1=8580)
#define SIDMODE (*(volatile uint8_t *)0xd63c)
/// Hypervisor traps
#define HYPERVISOR (*(volatile struct __hypervisor *)0xd640)
/// Math busy flag
#define MATHBUSY (*(volatile uint8_t *)0xd70f)
/// Math accelerator
#define MATH (*(volatile struct __cpu_math *)0xd768)
/// Color Ram
#define COLORRAM (*(volatile uint8_t *)0xd800)
/// Default address of screen character matrix
#define DEFAULT_SCREEN (*(volatile uint8_t *)0x0800)
/// The CIA#1: keyboard matrix, joystick #1/#2
#define CIA1 (*(volatile struct __6526 *)0xdc00)
/// The CIA#2: Serial bus, RS-232, VIC memory bank
#define CIA2 (*(volatile struct __6526 *)0xdd00)
/// CIA#1 Interrupt for reading in ASM
#define CIA1_INTERRUPT (*(volatile uint8_t *)0xdc0d)
/// CIA#2 timer A&B as one single 32-bit value
#define CIA2_TIMER_AB (*(volatile uint32_t *)0xdd04)
/// CIA#2 Interrupt for reading in ASM
#define CIA2_INTERRUPT (*(volatile uint8_t *)0xdd0d)

/// Pointer to interrupt function
typedef void (*IRQ_TYPE)(void);
/// The vector used when the KERNAL serves IRQ interrupts
#define KERNEL_IRQ (*(volatile IRQ_TYPE *)0x0314)
/// The vector used when the KERNAL serves NMI interrupts
#define KERNEL_NMI (*(volatile IRQ_TYPE *)0x0318)
/// The vector used when the HARDWARE serves IRQ interrupts
#define HARDWARE_IRQ (*(volatile IRQ_TYPE *)0xfffe)

// C64 colors
#define COLOR_BLACK 0x00
#define COLOR_WHITE 0x01
#define COLOR_RED 0x02
#define COLOR_CYAN 0x03
#define COLOR_PURPLE 0x04
#define COLOR_GREEN 0x05
#define COLOR_BLUE 0x06
#define COLOR_YELLOW 0x07
#define COLOR_ORANGE 0x08
#define COLOR_BROWN 0x09
#define COLOR_LIGHTRED 0x0A
#define COLOR_GRAY1 0x0B
#define COLOR_GRAY2 0x0C
#define COLOR_LIGHTGREEN 0x0D
#define COLOR_LIGHTBLUE 0x0E
#define COLOR_GRAY3 0x0F

#ifdef __cplusplus
}
#endif
#endif // _MEGA65_H
