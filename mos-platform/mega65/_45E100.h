// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _45E100_H
#define _45E100_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
static_assert(sizeof(struct __45E100) == 16);
#endif

/// 45E100 Fast Ethernet controller commands
enum
#ifdef __clang__
    : uint8_t
#endif
{
  ETHERNET_STOPTX = 0,
  ETHERNET_STARTTX = 1,
  ETHERNET_RXNORMAL = 208,
  ETHERNET_DEBUGVIC = 212,
  ETHERNET_DEBUGCPU = 220,
  ETHERNET_RXONLYONE = 222,
  ETHERNET_FRAME1K = 241,
  ETHERNET_FRAME2K = 242
};

/*
 * The following masks are auto-generated from iomap.txt.
 * See https://github.com/dansanderson/mega65-symbols
 * Date: 2023-08-25
 */

enum
#ifdef __clang__
    : uint8_t
#endif
{
  /** Write 0 to hold ethernet controller under reset */
  ETH_RST_MASK = 0b00000001,
  /** Write 0 to hold ethernet controller transmit sub-system under reset
   */
  ETH_TXRST_MASK = 0b00000010,
  /** Read ethernet RX bits currently on the wire */
  ETH_DRXD_MASK = 0b00000100,
  /** Read ethernet RX data valid (debug) */
  ETH_DRXDV_MASK = 0b00001000,
  /** Allow remote keyboard input via magic ethernet frames */
  ETH_KEYEN_MASK = 0b00010000,
  /** Indicate if ethernet RX is blocked until RX buffers freed */
  ETH_RXBLKD_MASK = 0b01000000,
  /** Ethernet transmit side is idle, i.e., a packet can be sent. */
  ETH_TXIDLE_MASK = 0b10000000,
  /** Number of free receive buffers */
  ETH_RXBF_MASK = 0b00000110,
  /** Enable streaming of CPU instruction stream or VIC-IV display on
   * ethernet
   */
  ETH_STRM_MASK = 0b00001000,
  /** Ethernet TX IRQ status */
  ETH_TXQ_MASK = 0b00010000,
  /** Ethernet RX IRQ status */
  ETH_RXQ_MASK = 0b00100000,
  /** Enable ethernet TX IRQ */
  ETH_TXQEN_MASK = 0b01000000,
  /** Enable ethernet RX IRQ */
  ETH_RXQEN_MASK = 0b10000000,
  /** Ethernet disable promiscuous mode */
  ETH_NOPROM_MASK = 0b00000001,
  /** Disable CRC check for received packets */
  ETH_NOCRC_MASK = 0b00000010,
  /** Ethernet TX clock phase adjust */
  ETH_TXPH_MASK = 0b00001100,
  /** Accept broadcast frames */
  ETH_BCST_MASK = 0b00010000,
  /** Accept multicast frames */
  ETH_MCST_MASK = 0b00100000,
  /** Ethernet RX clock phase adjust */
  ETH_RXPH_MASK = 0b11000000,
  /** Ethernet MIIM register number */
  ETH_MIIMREG_MASK = 0b00011111,
  /** Ethernet MIIM PHY number (use 0 for Nexys4, 1 for MEGA65 r1 PCBs) */
  ETH_MIIMPHY_MASK = 0b11100000
};

#ifdef __cplusplus
} // extern block
#endif
#endif // header
