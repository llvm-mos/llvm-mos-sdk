// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

/*
MIT License

Copyright (c) 2023 The MEGA65 Community

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

/*
 * The following masks are auto-generated from iomap.txt.
 * See https://github.com/mega65/mega65-symbols
 */

/** Write 0 to hold ethernet controller under reset */
#define ETH_RST_MASK 0b00000001

/** Write 0 to hold ethernet controller transmit sub-system under reset */
#define ETH_TXRST_MASK 0b00000010

/** Read ethernet RX bits currently on the wire */
#define ETH_DRXD_MASK 0b00000100

/** Read ethernet RX data valid (debug) */
#define ETH_DRXDV_MASK 0b00001000

/** Allow remote keyboard input via magic ethernet frames */
#define ETH_KEYEN_MASK 0b00010000

/** Indicate if ethernet RX is blocked until RX buffers freed */
#define ETH_RXBLKD_MASK 0b01000000

/** Ethernet transmit side is idle, i.e., a packet can be sent. */
#define ETH_TXIDLE_MASK 0b10000000

/** Number of free receive buffers */
#define ETH_RXBF_MASK 0b00000110

/** Enable streaming of CPU instruction stream or VIC-IV display on ethernet */
#define ETH_STRM_MASK 0b00001000

/** Ethernet TX IRQ status */
#define ETH_TXQ_MASK 0b00010000

/** Ethernet RX IRQ status */
#define ETH_RXQ_MASK 0b00100000

/** Enable ethernet TX IRQ */
#define ETH_TXQEN_MASK 0b01000000

/** Enable ethernet RX IRQ */
#define ETH_RXQEN_MASK 0b10000000

/** Ethernet disable promiscuous mode */
#define ETH_NOPROM_MASK 0b00000001

/** Disable CRC check for received packets */
#define ETH_NOCRC_MASK 0b00000010

/** Ethernet TX clock phase adjust */
#define ETH_TXPH_MASK 0b00001100

/** Accept broadcast frames */
#define ETH_BCST_MASK 0b00010000

/** Accept multicast frames */
#define ETH_MCST_MASK 0b00100000

/** Ethernet RX clock phase adjust */
#define ETH_RXPH_MASK 0b11000000

/** Ethernet MIIM register number */
#define ETH_MIIMREG_MASK 0b00011111

/** Ethernet MIIM PHY number (use 0 for Nexys4, 1 for MEGA65 r1 PCBs) */
#define ETH_MIIMPHY_MASK 0b11100000

#ifdef __cplusplus
} // extern block
#endif
#endif // header
