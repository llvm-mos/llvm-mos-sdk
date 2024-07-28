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
  uint8_t ch0lvol;          //!< Audio DMA channel 0 left channel volume (offset 0x1e)
  uint8_t ch1lvol;          //!< Audio DMA channel 1 left channel volume (offset 0x1f)
  union {
    struct DMAAudioChannel ch0; //!< Audio DMA channel 0 (offset 0x20)
    struct {
      uint8_t ch0en; //!< Enable Audio DMA channel 0 (offset 0x20)
      uint8_t
          ch0baddrl; //!< Audio DMA channel X current address LSB (offset 0x21)
      uint8_t ch0baddrc; //!< Audio DMA channel X current address middle byte
                         //!< (offset 0x22)
      uint8_t
          ch0baddrm; //!< Audio DMA channel X current address MSB (offset 0x23)
      uint8_t ch0freql; //!< Audio DMA channel X frequency LSB (offset 0x24)
      uint8_t
          ch0freqc; //!< Audio DMA channel X frequency middle byte (offset 0x25)
      uint8_t ch0freqm;  //!< Audio DMA channel X frequency MSB (offset 0x26)
      uint8_t ch0taddrl; //!< Audio DMA channel X top address LSB (offset 0x27)
      uint8_t ch0taddrm; //!< Audio DMA channel X top address MSB (offset 0x28)
      uint8_t ch0volume; //!< Audio DMA channel X playback volume (offset 0x29)
      uint8_t ch0curaddrl; //!< Audio DMA channel X current address LSB (offset
                           //!< 0x2a)
      uint8_t ch0curaddrc; //!< Audio DMA channel X current address middle byte
                           //!< (offset 0x2b)
      uint8_t ch0curaddrm; //!< Audio DMA channel X current address MSB (offset
                           //!< 0x2c)
      uint8_t
          ch0tmraddrl; //!< Audio DMA channel X timing counter LSB (offset 0x2d)
      uint8_t ch0tmraddrc; //!< Audio DMA channel X timing counter middle byte
                           //!< (offset 0x2e)
      uint8_t
          ch0tmraddrm; //!< Audio DMA channel X timing counter MSB (offset 0x2f)
    };
  };
  uint8_t ch1en;          //!< Enable Audio DMA channel 1 (offset 0x30)
  uint8_t ch1baddrl;        //!< Audio DMA channel X current address LSB (offset 0x31)
  uint8_t ch1baddrc;        //!< Audio DMA channel X current address middle byte (offset 0x32)
  uint8_t ch1baddrm;        //!< Audio DMA channel X current address MSB (offset 0x33)
  uint8_t ch1freql;         //!< Audio DMA channel X frequency LSB (offset 0x34)
  uint8_t ch1freqc;         //!< Audio DMA channel X frequency middle byte (offset 0x35)
  uint8_t ch1freqm;         //!< Audio DMA channel X frequency MSB (offset 0x36)
  uint8_t ch1taddrl;        //!< Audio DMA channel X top address LSB (offset 0x37)
  uint8_t ch1taddrm;        //!< Audio DMA channel X top address MSB (offset 0x38)
  uint8_t ch1volume;        //!< Audio DMA channel X playback volume (offset 0x39)
  uint8_t ch1curaddrl;      //!< Audio DMA channel X current address LSB (offset 0x3a)
  uint8_t ch1curaddrc;      //!< Audio DMA channel X current address middle byte (offset 0x3b)
  uint8_t ch1curaddrm;      //!< Audio DMA channel X current address MSB (offset 0x3c)
  uint8_t ch1tmraddrl;      //!< Audio DMA channel X timing counter LSB (offset 0x3d)
  uint8_t ch1tmraddrc;      //!< Audio DMA channel X timing counter middle byte (offset 0x3e)
  uint8_t ch1tmraddrm;      //!< Audio DMA channel X timing counter MSB (offset 0x3f)
  uint8_t ch2en;            //!< Enable Audio DMA channel 2 (offset 0x40)
  uint8_t ch2baddrl;        //!< Audio DMA channel X current address LSB (offset 0x41)
  uint8_t ch2baddrc;        //!< Audio DMA channel X current address middle byte (offset 0x42)
  uint8_t ch2baddrm;        //!< Audio DMA channel X current address MSB (offset 0x43)
  uint8_t ch2freql;         //!< Audio DMA channel X frequency LSB (offset 0x44)
  uint8_t ch2freqc;         //!< Audio DMA channel X frequency middle byte (offset 0x45)
  uint8_t ch2freqm;         //!< Audio DMA channel X frequency MSB (offset 0x46)
  uint8_t ch2taddrl;        //!< Audio DMA channel X top address LSB (offset 0x47)
  uint8_t ch2taddrm;        //!< Audio DMA channel X top address MSB (offset 0x48)
  uint8_t ch2volume;        //!< Audio DMA channel X playback volume (offset 0x49)
  uint8_t ch2curaddrl;      //!< Audio DMA channel X current address LSB (offset 0x4a)
  uint8_t ch2curaddrc;      //!< Audio DMA channel X current address middle byte (offset 0x4b)
  uint8_t ch2curaddrm;      //!< Audio DMA channel X current address MSB (offset 0x4c)
  uint8_t ch2tmraddrl;      //!< Audio DMA channel X timing counter LSB (offset 0x4d)
  uint8_t ch2tmraddrc;      //!< Audio DMA channel X timing counter middle byte (offset 0x4e)
  uint8_t ch2tmraddrm;      //!< Audio DMA channel X timing counter MSB (offset 0x4f)
  uint8_t ch3en;            //!< Enable Audio DMA channel 3 (offset 0x50)
  uint8_t ch3baddrl;        //!< Audio DMA channel X current address LSB (offset 0x51)
  uint8_t ch3baddrc;        //!< Audio DMA channel X current address middle byte (offset 0x52)
  uint8_t ch3baddrm;        //!< Audio DMA channel X current address MSB (offset 0x53)
  uint8_t ch3freql;         //!< Audio DMA channel X frequency LSB (offset 0x54)
  uint8_t ch3freqc;         //!< Audio DMA channel X frequency middle byte (offset 0x55)
  uint8_t ch3freqm;         //!< Audio DMA channel X frequency MSB (offset 0x56)
  uint8_t ch3taddrl;        //!< Audio DMA channel X top address LSB (offset 0x57)
  uint8_t ch3taddrm;        //!< Audio DMA channel X top address MSB (offset 0x58)
  uint8_t ch3volume;        //!< Audio DMA channel X playback volume (offset 0x59)
  uint8_t ch3curaddrl;      //!< Audio DMA channel X current address LSB (offset 0x5a)
  uint8_t ch3curaddrc;      //!< Audio DMA channel X current address middle byte (offset 0x5b)
  uint8_t ch3curaddrm;      //!< Audio DMA channel X current address MSB (offset 0x5c)
  uint8_t ch3tmraddrl;      //!< Audio DMA channel X timing counter LSB (offset 0x5d)
  uint8_t ch3tmraddrc;      //!< Audio DMA channel X timing counter middle byte (offset 0x5e)
  uint8_t ch3tmraddrm;      //!< Audio DMA channel X timing counter MSB (offset 0x5f)
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
