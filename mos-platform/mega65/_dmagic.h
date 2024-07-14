// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _DMAGIC_H
#define _DMAGIC_H

#ifndef __cplusplus
#include <stddef.h>
#include <stdint.h>
#endif

/// DMA commands
enum
#ifdef __clang__
    : uint8_t
#endif
{
  DMA_COPY_CMD = 0x00, //!< DMA copy command
  DMA_MIX_CMD = 0x01,  //!< DMA mix command (unimplemented)
  DMA_SWAP_CMD = 0x02, //!< DMA swap command (unimplemented)
  DMA_FILL_CMD = 0x03, //!< DMA fill command
};

/// Addressing modes
enum
#ifdef __clang__
    : uint8_t
#endif
{
  DMA_LINEAR_ADDR = 0x00, //!< DMA linear (normal) addressing mode
  DMA_MODULO_ADDR = 0x01, //!< DMA modulo (rectangular) addressing mode
  DMA_HOLD_ADDR = 0x02,   //!< DMA hold (constant address) addressing mode
  DMA_XYMOD_ADDR =
      0x03 //!< DMA XY MOD (bitmap rectangular) addressing mode (unimplemented)
};

/// BANK and FLAGS field has the following structure
enum
#ifdef __clang__
    : uint8_t
#endif
{
  DMA_HOLD = 0b00010000,      //!< Do not change the address (bit 4)
  DMA_MODULO = 0b00100000,    //!< Apply the MODULO field to wrap around (bit 5)
  DMA_DIRECTION = 0b01000000, //!< Apply the MODULO field to wrap around (bit 6)
  DMA_IO = 0b10000000, //!< I/O registers visible during the DMA controller at
                       //!< $D000–$DFFF (bit 7).
};

/// DMA options
enum
#ifdef __clang__
    : uint8_t
#endif
{
  /// Use 11 byte F011A DMA list format [no value]
  ENABLE_F018A_OPT = 0x0a,
  /// Use 12 byte F011B DMA list format [no value]
  ENABLE_F018B_OPT = 0x0b,
  /// Source address bits 20 – 27 [value follows]
  SRC_ADDR_BITS_OPT = 0x80,
  /// Destination address bits 20 – 27 [value follows]
  DST_ADDR_BITS_OPT = 0x81,
  /// Destination skip rate (whole bytes) [value follows]
  DST_SKIP_RATE_OPT = 0x85,
};

/// The F018 "DMAgic" DMA controller at 0xd700
struct DMAgicController {
  uint8_t addr_lsb_trigger; //!< offset 0x00
  uint8_t addr_msb;         //!< offset 0x01
  uint8_t addr_bank;        //!< offset 0x02, writing clears $d704
  uint8_t enable_f018b;     //!< offset 0x03, extensed fields
  uint8_t addr_mb;          //!< offset 0x04
  uint8_t trigger_enhanced; //!< offset 0x05
  uint8_t etrigmapd;        //!< offset 0x06
  uint8_t unused1[7];       //!< offset 0x07-0x0d
  uint8_t addr_lsb;         //!< offset 0x0e
  uint8_t unused2[2];       //!< offset 0x0f-0x10
};

/// Older 11 byte DMA list structure; also known as just "F018"
struct DMAList_F018A {
  uint8_t command;      //!< offset 0x00
  uint16_t count;       //!< offset 0x01
  uint16_t source_addr; //!< offset 0x03
  uint8_t source_bank;  //!< offset 0x05
  uint16_t dest_addr;   //!< offset 0x06
  uint8_t dest_bank;    //!< offset 0x08
  uint16_t modulo;      //!< offset 0x09
};

/// Newer 12-byte "F018B" DMA list structure
struct DMAList_F018B {
  uint8_t command;      //!< offset 0x00
  uint16_t count;       //!< offset 0x01
  uint16_t source_addr; //!< offset 0x03
  uint8_t source_bank;  //!< offset 0x05
  uint16_t dest_addr;   //!< offset 0x06
  uint8_t dest_bank;    //!< offset 0x08
  uint8_t command_msb;  //!< offset 0x09
  uint16_t modulo;      //!< offset 0x0a
};

#endif
