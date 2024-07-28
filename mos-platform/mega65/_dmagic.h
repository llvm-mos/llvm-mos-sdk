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

/// DMA audio channel structure
struct DMAAudioChannel {
  uint8_t enable; //!< Enable Audio DMA channel X (offset 0x00)
  union {
    struct {
      uint8_t baddr_lsb; //!< base address LSB (offset 0x01)
      uint8_t baddr_msb; //!< base address MSB (offset 0x02)
      uint8_t baddr_mb;  //!< base address middle byte (offset 0x03)
    };
#if (__STDC_VERSION__ >= 202000)
    unsigned _BitInt(24) baddr; //!< 24-bit base address (offset 0x01)
#endif
  };
  union {
    struct {
      uint8_t freq_lsb; //!< frequency LSB (offset 0x04)
      uint8_t freq_mb;  //!< frequency middle byte (offset 0x05)
      uint8_t freq_msb; //!< frequency MSB (offset 0x06)
    };
#if (__STDC_VERSION__ >= 202000)
    unsigned _BitInt(24) freq; //!< 24-bit frequency (offset 0x04)
#endif
  };
  union {
    struct {
      uint8_t taddr_lsb; //!< top address LSB (offset 0x07)
      uint8_t taddr_msb; //!< top address MSB (offset 0x08)
    };
#if (__STDC_VERSION__ >= 202000)
    unsigned _BitInt(16) taddr; //!< 16-bit top address (offset 0x07)
#endif
  };
  uint8_t volume; //!< playback volume (offset 0x09)
  union {
    struct {
      uint8_t curaddr_lsb; //!< current address LSB (offset 0x0a)
      uint8_t curaddr_mb;  //!< current address middle byte (offset 0x0b)
      uint8_t curaddr_msb; //!< current address MSB (offset 0x0c)
    };
#if (__STDC_VERSION__ >= 202000)
    unsigned _BitInt(24) curaddr; //!< 24-bit current address (offset 0x0a)
#endif
  };
  union {
    struct {
      uint8_t tmraddr_lsb; //!< timing counter LSB (offset 0x0d)
      uint8_t tmraddr_mb;  //!< timing counter middle byte (offset 0x0e)
      uint8_t tmraddr_msb; //!< timing counter MSB (offset 0x0f)
    };
#if (__STDC_VERSION__ >= 202000)
    unsigned _BitInt(24) tmraddr; //!< 24-bit timing counter (offset 0x0d)
#endif
  };
};

#ifdef __cplusplus
static_assert(sizeof(DMAAudioChannel) == 0x10);
#endif

/// Bitflags for controlling the DMA audio enable register ($d711)
enum
#ifdef __clang__
    : uint8_t
#endif
{
  DMA_AUDEN = 0b10000000,     //!< Enable Audio DMA
  DMA_BLKD = 0b01000000,      //!< Block DMA
  DMA_AUD_WRBLK = 0b00100000, //!< Audio write block
  DMA_NOMIX = 0b00010000,     //!< No mix
  DMA_AUDBLKTO = 0b00000111,  //!< Audio block timeout (DEBUG) Bits 0-2
};

/// Bitflags for controlling individual DMA audio channel enable registers
/// ($d720, etc)
enum
#ifdef __clang__
    : uint8_t
#endif
{
  DMA_CHENABLE = 0b10000000,   //!< Enable channel
  DMA_CHLOOP = 0b01000000,     //!< Channel looping
  DMA_CHSGN = 0b00100000,      //!< Use signed samples
  DMA_CHSINE = 0b00010000,     //!< Play 32-sample sine wave instead of DMA data
  DMA_CHSTP = 0b00001000,      //!< Stop flag
  DMA_CHSBITS_16 = 0b00000011, //!< 16-bit samples
  DMA_CHSBITS_8 = 0b00000010,  //!< 8-bit samples
};

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
