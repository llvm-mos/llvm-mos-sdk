// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

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

/// 45E100 Fast Ethernet controller
///
/// Enabled by writing 0x53 and then 0x47 to VIC-IV register 0xD02F
struct __45E100 {
  uint8_t ctrl1; //!< Control register 1 (offset 0x00)
  uint8_t ctrl2; //!< Control register 2 (offset 0x01)
  union {
    uint16_t txsz; //!< X Packet size (offset 0x02)
    struct {
      uint8_t txsz_lsb; //!< X Packet size (low byte) (offset 0x02)
      uint8_t txsz_msb; //!< X Packet size (high byte) (offset 0x03)
    };
  };
  uint8_t command; //!< Write-only command register (offset 0x04)
  uint8_t ctrl3;   //!< Control register 3 (offset 0x05)
  /// MIIM PHY number (use 0 for Nexys4, 1 for MEGA65 r1 PCBs)
  /// and MIIM register number (offset 0x06)
  uint8_t miim_phy_reg;
  uint16_t miimv;     //!< MIIM register value (offset 0x07)
  uint8_t macaddr[6]; //!< MAC address (offset 0x09)
};
#ifdef __cplusplus
static_assert(sizeof(struct __45E100) == 15);
#endif

/// 45E100 Fast Ethernet controller commands
enum {
  ETHERNET_STOPTX = 0,
  ETHERNET_STARTTX = 1,
  ETHERNET_RXNORMAL = 208,
  ETHERNET_DEBUGVIC = 212,
  ETHERNET_DEBUGCPU = 220,
  ETHERNET_RXONLYONE = 222,
  ETHERNET_FRAME1K = 241,
  ETHERNET_FRAME2K = 242
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
} // extern block
#endif
#endif // _MEGA65_H
