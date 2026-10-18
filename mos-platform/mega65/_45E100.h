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
/// Map the controller's buffers over 0xD000-0xDFFF by writing
/// VIC4_KEY_ETH_A then VIC4_KEY_ETH_B to VICIV.key.
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
  /// Debug window (offset 0x0f). Reports whatever was last written to it;
  /// 0 selects buffer identities, low two bits being the CPU's read buffer.
  uint8_t debug;
};
#ifdef __cplusplus
static_assert(sizeof(struct __45E100) == 16);
#else
_Static_assert(sizeof(struct __45E100) == 16, "45E100 block is $D6E0-$D6EF");
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
  /* ctrl1 ($D6E0) */
  /** Write 0 to hold the controller under reset */
  ETH_RST_MASK = 0b00000001,
  /** Write 0 to hold the transmit sub-system under reset */
  ETH_TXRST_MASK = 0b00000010,
  /** Read ethernet RX bits currently on the wire */
  ETH_DRXD_MASK = 0b00000100,
  /** Read ethernet RX data valid (debug) */
  ETH_DRXDV_MASK = 0b00001000,
  /** Allow remote keyboard input via magic ethernet frames. Reads back as
      the remote-control enable status. */
  ETH_KEYEN_MASK = 0b00010000,
  /** RX is blocked until receive buffers are freed */
  ETH_RXBLKD_MASK = 0b01000000,
  /** Transmit side is idle, i.e. a packet can be sent */
  ETH_TXIDLE_MASK = 0b10000000,

  /* ctrl2 ($D6E1) */
  /** Number of free receive buffers. Read only; writing bit 1 is
      ETH_RXROTATE_MASK instead. */
  ETH_RXBF_MASK = 0b00000110,
  /** Write to hand back the current receive buffer and present the next
      frame. Edge triggered, so it takes a write with the bit clear followed
      by one with it set. */
  ETH_RXROTATE_MASK = 0b00000010,
  /** Enable streaming of CPU instruction stream or VIC-IV display */
  ETH_STRM_MASK = 0b00001000,
  /** Indicate if ethernet TX is idle */
  ETH_TXQ_MASK = 0b00010000,
  /** Indicate if a received frame is waiting */
  ETH_RXQ_MASK = 0b00100000,
  /** Enable ethernet TX IRQ */
  ETH_TXQEN_MASK = 0b01000000,
  /** Enable ethernet RX IRQ */
  ETH_RXQEN_MASK = 0b10000000,

  /* ctrl3 ($D6E5) */
  /** Disable promiscuous mode. iomap.txt annotates this bit twice, as
      "disable promiscuous mode" and as "enable filtering of unicast frames
      if MAC address does not match", and annotates ETH_MCST_MASK as both the
      multicast and the unicast enable. Which reading is right has not been
      settled here; matching addresses in software avoids the question. */
  ETH_NOPROM_MASK = 0b00000001,
  /** Disable CRC check for received packets */
  ETH_NOCRC_MASK = 0b00000010,
  /** TX clock phase, a two-bit field: use ETH_TXPH_SHIFT */
  ETH_TXPH_MASK = 0b00001100,
  ETH_TXPH_SHIFT = 2,
  /** Accept broadcast frames */
  ETH_BCST_MASK = 0b00010000,
  /** Accept multicast frames (see ETH_NOPROM_MASK) */
  ETH_MCST_MASK = 0b00100000,
  /** RX clock phase, a two-bit field: use ETH_RXPH_SHIFT */
  ETH_RXPH_MASK = 0b11000000,
  ETH_RXPH_SHIFT = 6,

  /* miim_phy_reg ($D6E6) */
  /** MIIM register number */
  ETH_MIIMREG_MASK = 0b00011111,
  /** MIIM PHY number */
  ETH_MIIMPHY_MASK = 0b11100000
};

#ifdef __cplusplus
} // extern block
#endif
#endif // header
