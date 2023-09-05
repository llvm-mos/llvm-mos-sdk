// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

/*
MIT License

Copyright (c) 2023 Mikael Lund aka Wombat

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _MEGA65_H
#define _MEGA65_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wnested-anon-types"
#pragma clang diagnostic ignored "-Wgnu-binary-literal"
#pragma clang diagnostic ignored "-Wfixed-enum-extension"
#endif

#include <_45E100.h>
#include <_6526.h>
#include <_sid.h>
#include <_vic2.h>
#include <_vic3.h>
#include <_vic4.h>

/// Hypervisor registers (0xD640-0xD67F)
struct __hypervisor {
  union {
    uint8_t htrap[64];
    struct {
      /// Hypervisor A register storage
      uint8_t rega; // 0xD640
      /// Hypervisor X register storage
      uint8_t regx;    // 0xD641
      uint8_t unused1; // 0xD642
      /// Hypervisor Z register storage
      uint8_t regz; // 0xD643
      /// Hypervisor B register storage
      uint8_t regb; // 0xD644
      /// Hypervisor SPL register storage
      uint8_t spl; // 0xD645
      /// Hypervisor SPH register storage
      uint8_t sph; // 0xD646
      /// Hypervisor P register storage
      uint8_t pflags; // 0xD647
      /// Hypervisor PC-low register storage
      uint8_t pcl; // 0xD648
      /// Hypervisor PC-high register storage
      uint8_t pch;     // 0xD649
      uint8_t maplo1;  // 0xD64A
      uint8_t maplo2;  // 0xD64B
      uint8_t maphi1;  // 0xD64C
      uint8_t maphi2;  // 0xD64D
      uint8_t maplomb; // 0xD64E
      uint8_t maphimb; // 0xD64F
      /// Hypervisor CPU port $00 value
      uint8_t port00; // 0xD650
      /// Hypervisor CPU port $01 value
      uint8_t port01;     // 0xD651
      uint8_t vicmode;    // 0xD652
      uint8_t dma_src_mb; // 0xD653
      /// Hypervisor DMAgic destination MB
      uint8_t dma_dst_hb; // 0xD654
      /// Hypervisor DMAGic list address
      uint32_t dmaladdr;   // 0xD655
      uint8_t vflop;       // 0xD659
      uint8_t unused2[22]; // 0xD65A
      /// Hypervisor GeoRAM base address (x MB)
      uint8_t georambase; // 0xD670
      /// Hypervisor GeoRAM address mask (applied to GeoRAM block register)
      uint8_t georammask; // 0xD671
      /// Enable composited Matrix Mode, and disable UART access to serial
      /// monitor.
      uint8_t matrixen;   // 0xD672
      uint8_t unused3[9]; // 0xD673
      /// Hypervisor write serial output to UART monitor
      uint8_t uartdata; // 0xD67C
      uint8_t watchdog; // 0xD67D
      /// Hypervisor already-upgraded bit (writing sets permanently)
      uint8_t hicked; // 0xD67E
      /// Writing trigger return from hypervisor
      uint8_t enterexit; // 0xD67F
    };
  };
};
#ifdef __cplusplus
static_assert(sizeof(struct __hypervisor) == 64);
#endif

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
  union {
    struct {
      uint32_t multout_lsb;
      uint32_t multout_msb;
    };
#ifndef __CC65__
    uint64_t multout;
#endif
  };
  /// 32-bit programmable input (0xD780)
  uint32_t mathin[16];
};
#ifdef __cplusplus
static_assert(sizeof(__cpu_math) == 88);
#endif

/// RGB color palette
struct __color_palette {
  uint8_t red[256];   //!< Red palette values (reversed nybl order)
  uint8_t green[256]; //!< Green palette values (reversed nybl order)
  uint8_t blue[256];  //!< Blue palette values (reversed nybl order)
};

/// 6510/45GS10 CPU port DDR
#define CPU_PORTDDR (*(volatile uint8_t *)0x0000)
/// 6510/45GS10 CPU port data
#define CPU_PORT (*(volatile uint8_t *)0x0001)
/// Default address of screen character matrix
#define DEFAULT_SCREEN (*(volatile uint8_t *)0x0800)
/// The VIC-II
#define VICII (*(volatile struct __vic2 *)0xd000)
/// The VIC IV
#define VICIV (*(volatile struct __vic4 *)0xd000)
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
/// Ethernet controller
#define ETHERNET (*(volatile struct __45E100 *)0xd6e0)
/// Math busy flag
#define MATHBUSY (*(volatile uint8_t *)0xd70f)
/// Math accelerator
#define MATH (*(volatile struct __cpu_math *)0xd768)
/// The CIA 1
#define CIA1 (*(volatile struct __6526 *)0xdc00)
/// The CIA 2
#define CIA2 (*(volatile struct __6526 *)0xdd00)

// C64 colors
enum
#ifdef __clang__
    : uint8_t
#endif
{
  COLOR_BLACK = 0x00,
  COLOR_WHITE = 0x01,
  COLOR_RED = 0x02,
  COLOR_CYAN = 0x03,
  COLOR_PURPLE = 0x04,
  COLOR_GREEN = 0x05,
  COLOR_BLUE = 0x06,
  COLOR_YELLOW = 0x07,
  COLOR_ORANGE = 0x08,
  COLOR_BROWN = 0x09,
  COLOR_LIGHTRED = 0x0A,
  COLOR_GRAY1 = 0x0B,
  COLOR_GRAY2 = 0x0C,
  COLOR_LIGHTGREEN = 0x0D,
  COLOR_LIGHTBLUE = 0x0E,
  COLOR_GRAY3 = 0x0F
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef __cplusplus
} // extern block
#endif
#endif // _MEGA65_H
