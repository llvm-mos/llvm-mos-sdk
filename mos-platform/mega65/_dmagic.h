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
  DMA_HOLD = 16,      //!< Do not change the address (bit 4)
  DMA_MODULO = 32,    //!< Apply the MODULO field to wrap around (bit 5)
  DMA_DIRECTION = 64, //!< Apply the MODULO field to wrap around (bit 6)
  DMA_IO = 128, //!< I/O registers visible during the DMA controller at
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

/// @brief DMA audio channel structure
struct DMAAudioChannel {
  uint8_t enable;      //!< Enable Audio DMA channel X (offset 0x00)
  uint8_t baddr_lsb;   //!< Audio DMA channel X current address LSB (offset 0x01)
  uint8_t baddr_msb;   //!< Audio DMA channel X current address MSB (offset 0x02)
  uint8_t baddr_mb;    //!< Audio DMA channel X current address middle byte (offset 0x03)
  uint8_t freq_lsb;    //!< Audio DMA channel X frequency LSB (offset 0x04)
  uint8_t freq_mb;     //!< Audio DMA channel X frequency middle byte (offset 0x05)
  uint8_t freq_msb;    //!< Audio DMA channel X frequency MSB (offset 0x06)
  uint8_t taddr_lsb;   //!< Audio DMA channel X top address LSB (offset 0x07)
  uint8_t taddr_msb;   //!< Audio DMA channel X top address MSB (offset 0x08)
  uint8_t volume;      //!< Audio DMA channel X playback volume (offset 0x09)
  uint8_t curaddr_lsb; //!< Audio DMA channel X current address LSB (offset 0x0a)
  uint8_t curaddr_mb;  //!< Audio DMA channel X current address middle byte (offset 0x0b)
  uint8_t curaddr_msb; //!< Audio DMA channel X current address MSB (offset 0x0c)
  uint8_t tmraddr_lsb; //!< Audio DMA channel X timing counter LSB (offset 0x0d)
  uint8_t tmraddr_mb;  //!< Audio DMA channel X timing counter middle byte (offset 0x0e)
  uint8_t tmraddr_msb; //!< Audio DMA channel X timing counter MSB (offset 0x0f)
};

#ifdef __cplusplus
static_assert(sizeof(DMAAudioChannel) == 0x10);
#endif

/// The F018 "DMAgic" DMA controller at 0xd700
struct DMAgicController {
  uint8_t addr_lsb_trigger; //!< DMAgic DMA list address LSB, and trigger DMA (when written) (offset 0x00)
  uint8_t addr_msb;         //!< DMA list address high byte (address bits 8 – 15) (offset 0x01)
  uint8_t addr_bank;        //!< DMA list address bank (address bits 16 – 22). Writing clears $D704 (offset 0x02)
  uint8_t enable_f018b;     //!< offset 0x03, extensed fields
  uint8_t addr_mb;          //!< DMA list address mega-byte (offset 0x04)
  uint8_t trigger_enhanced; //!< Set low-order byte of DMA list address, and trigger Enhanced DMA job (offset 0x05)
  uint8_t etrigmapd;        //!< Set low-order byte of DMAlistaddress and trigger EnhancedDMA job, with list in current CPU memory map (offset 0x06)
  uint8_t unused1[7];       //!< offset 0x07-0x0d
  uint8_t addr_lsb;         //!< DMA list address low byte (address bits 0 – 7) WITHOUT STARTING A DMA JOB (offset 0x0e)
  uint8_t unused2[2];       //!< offset 0x0f-0x10
  uint8_t auden;            //!< Enable Audio DMA (offset 0x11)
  uint8_t unused3[10];      //!< offset 0x12-0x1b
  uint8_t ch0rvol;          //!< Audio DMA channel 0 right channel volume (offset 0x1c)
  uint8_t ch1rvol;          //!< Audio DMA channel 1 right channel volume (offset 0x1d)
  uint8_t ch2lvol;          //!< Audio DMA channel 2 left channel volume (offset 0x1e)
  uint8_t ch3lvol;          //!< Audio DMA channel 3 left channel volume (offset 0x1f)
  union {
    struct {
      struct DMAAudioChannel ch0; //!< Audio DMA channel 0 (offset 0x20)
      struct DMAAudioChannel ch1; //!< Audio DMA channel 1 (offset 0x30)
      struct DMAAudioChannel ch2; //!< Audio DMA channel 2 (offset 0x40)
      struct DMAAudioChannel ch3; //!< Audio DMA channel 3 (offset 0x50)
    };
    struct DMAAudioChannel channel[4]; //!< Audio channels as an array (offset 0x20)
  };
};

#ifdef __cplusplus
static_assert(sizeof(DMAgicController) == 0x60);
#endif

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
