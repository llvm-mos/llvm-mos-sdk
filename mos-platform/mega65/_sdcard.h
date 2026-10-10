// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _SDCARD_H
#define _SDCARD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// MEGA65 SD card controller
///
/// Needs the MEGA65 I/O personality, which VICIV.key selects; see _vic4.h.
///
/// Sector data does not pass through these registers. It lives in a 512-byte
/// buffer, reached at 0xFFD6E00 by DMA or 32-bit addressing, or at 0xDE00 in
/// the ordinary I/O window once SDCARD_MAP_BUFFER has put it there and colour
/// RAM is elsewhere than 0xDC00.
struct __sdcard {
  union {
    uint8_t command; //!< Command to the controller, SDCARD_* (offset 0x00)
    uint8_t status;  //!< Controller status, SD_*_MASK (offset 0x00)
  };
  union {
    /// Sector to read or write, low byte first (offset 0x01)
    ///
    /// Four independent latches, sampled only when a command is written, so
    /// the order they are set in does not matter. Index with a uint8_t: an
    /// int index costs a zero-page pointer instead of absolute addressing.
    uint8_t sector[4];
    uint32_t sector_number; //!< The same four registers as one number
  };
  uint8_t state; //!< (read only) controller state, for debugging (offset 0x05)
  union {
    uint8_t fill_value; //!< Byte written to a whole sector in fill mode (0x06)
    uint8_t data_token; //!< (read only) the card's last data token (0x06)
  };
  uint8_t last_byte;   //!< (read only) most recent byte read (offset 0x07)
  uint8_t f011_bufptr; //!< (read only) F011 buffer pointer, low byte (0x08)
  uint8_t control;     //!< Buffer and drive control, SD_*_MASK (offset 0x09)
};

/// F011 floppy emulation: which disk image each drive uses, and where it is
///
/// Writable in hypervisor mode only, so an ordinary program's writes here are
/// discarded without a word. The readable bits are not the writable ones
/// either: image_type reads machine state and writes the two D64 flags.
struct __sdfdc {
  uint8_t image_type; //!< Machine state read, D64 flags written (offset 0x00)
  uint8_t flags;      //!< Per-drive image flags, SDFDC_*_MASK (offset 0x01)
  union {
    uint8_t d0_start_sector[4]; //!< Drive 0 image's first sector (offset 0x02)
    uint32_t d0_start;
  };
  union {
    uint8_t d1_start_sector[4]; //!< Drive 1 image's first sector (offset 0x06)
    uint32_t d1_start;
  };
};

// On the target only. A host aligns the 32-bit members and pads the structs,
// and code that includes <mega65.h> to test its arithmetic natively should
// still compile. The sibling headers guard on __cplusplus instead, which does
// not buy them that: a host C++ build fails on __45E100's assert as it stands.
#ifdef __mos__
#ifdef __cplusplus
static_assert(sizeof(struct __sdcard) == 10);
static_assert(sizeof(struct __sdfdc) == 10);
#else
_Static_assert(sizeof(struct __sdcard) == 10, "SD controller is $D680-$D689");
_Static_assert(sizeof(struct __sdfdc) == 10, "F011 image state is $D68A-$D693");
#endif
#endif

/// MEGA65 SD card controller commands
///
/// A reset is SDCARD_RESET_BEGIN then SDCARD_RESET_END, and it returns the
/// card to byte addressing: one that answered SD_SDHC_MASK needs
/// SDCARD_SDHC_MODE_ON again, or every sector number is taken as a byte
/// offset and no transfer finishes.
enum
#ifdef __clang__
    : uint8_t
#endif
{
  SDCARD_RESET_BEGIN = 0x00,
  SDCARD_RESET_END = 0x01,
  SDCARD_READ_SECTOR = 0x02,
  SDCARD_WRITE_SECTOR = 0x03,
  SDCARD_WRITE_MULTI_FIRST = 0x04,
  SDCARD_WRITE_MULTI_NEXT = 0x05,
  SDCARD_WRITE_MULTI_LAST = 0x06,
  SDCARD_FLUSH_CACHE = 0x0c,     /** Flush the card's own write cache */
  SDCARD_SDHC_MODE_OFF = 0x40,   /** Address by byte */
  SDCARD_SDHC_MODE_ON = 0x41,    /** Address by sector */
  SDCARD_ERROR_CLEAR_OFF = 0x44, /** Stop clearing the error flags */
  SDCARD_ERROR_CLEAR_ON = 0x45,  /** Clear the error flags */
  /// Open the write gate for sector zero. A write needs a gate open, and
  /// which one depends on the sector: this for sector zero, SDCARD_WRITE_GATE
  /// for any other. Each lasts about a millisecond, and the wrong one leaves
  /// the write refused with the error bits set -- which is what keeps a stray
  /// write off a card's own boot sector.
  SDCARD_WRITE_GATE_SECTOR0 = 0x4d,
  SDCARD_WRITE_GATE = 0x57,       /** Write gate for any other sector */
  SDCARD_MAP_BUFFER = 0x81,       /** Show the sector buffer at 0xDE00 */
  SDCARD_UNMAP_BUFFER = 0x82,     /** Hide it again */
  SDCARD_FILL_MODE_ON = 0x83,     /** Write fill_value instead of the buffer */
  SDCARD_FILL_MODE_OFF = 0x84,    /** Write the buffer again */
  SDCARD_SELECT_PRIMARY = 0xc0,   /** Talk to the first card */
  SDCARD_SELECT_SECONDARY = 0xc1, /** Talk to the second */
};

/*
 * The following masks are auto-generated from iomap.txt.
 * See https://github.com/dansanderson/mega65-symbols
 * Date: 2023-08-25
 */

/* status ($D680) */
enum
#ifdef __clang__
    : uint8_t
#endif
{
  SD_SDIO_BUSY_MASK = 0b00000001,     /** SDIO side busy */
  SD_CARD_BUSY_MASK = 0b00000010,     /** The card says it is busy */
  SD_RESET_MASK = 0b00000100,         /** Controller held in reset */
  SD_BUFFER_MAPPED_MASK = 0b00001000, /** Sector buffer showing at 0xDE00 */
  SD_SDHC_MASK = 0b00010000,          /** Card is SDHC, so addressed by sector */
  SD_FSM_ERROR_MASK = 0b00100000,     /** SDIO state machine error */
  SD_ERROR_MASK = 0b01000000,         /** SDIO error */
  SD_SECONDARY_CARD_MASK = 0b10000000, /** Second card selected */
};

/* control ($D689) */
enum
#ifdef __clang__
    : uint8_t
#endif
{
  SD_BUFBIT8_MASK = 0b00000001,  /** (read only) bit 8 of the buffer pointer */
  SD_BUFFFULL_MASK = 0b00000010, /** (read only) a sector arrived, unread */
  SD_HNDSHK_MASK = 0b00000100,   /** The card's handshake signal */
  SD_DRDY_MASK = 0b00001000,     /** The card's data-ready signal */
  SD_FDCSWAP_MASK = 0b00100000,  /** Swap floppy drives 0 and 1 */
  /// Which sector buffer 0xFFD6E00 shows: set for the SD card's, clear for the
  /// F011's. Set it before writing a sector, or the write ships whatever the
  /// F011's buffer last held.
  SD_BUFFSEL_MASK = 0b10000000,
};

/* image_type ($D68A): bits 0-3 read machine state, bits 6-7 write the type */
enum
#ifdef __clang__
    : uint8_t
#endif
{
  SD_CDC00_MASK = 0b00000001,    /** (read only) colour RAM is at 0xDC00 */
  SD_VICIII_MASK = 0b00000010,   /** (read only) VIC-IV or ethernet bank shown */
  SD_VFDC0_MASK = 0b00000100,    /** (read only) drive 0 served over the monitor */
  SD_VFDC1_MASK = 0b00001000,    /** (read only) drive 1 served over the monitor */
  SDFDC_D0D64_MASK = 0b01000000, /** Drive 0 image is a D64, else a D81 */
  SDFDC_D1D64_MASK = 0b10000000, /** Drive 1 image is a D64, else a D81 */
};

/* flags ($D68B) */
enum
#ifdef __clang__
    : uint8_t
#endif
{
  SDFDC_D0IMG_MASK = 0b00000001, /** Drive 0 uses an image, else the real drive */
  SDFDC_D0P_MASK = 0b00000010,   /** Drive 0 has media */
  /// Drive 0 write *enable*, whatever the name iomap.txt gives it: the
  /// hardware stores and returns the complement, so setting this permits
  /// writes and clearing it protects the drive.
  SDFDC_D0WP_MASK = 0b00000100,
  SDFDC_D1IMG_MASK = 0b00001000, /** Drive 1 uses an image, else the real drive */
  SDFDC_D1P_MASK = 0b00010000,   /** Drive 1 has media */
  SDFDC_D1WP_MASK = 0b00100000,  /** Drive 1 write enable; see SDFDC_D0WP_MASK */
  SDFDC_D0MD_MASK = 0b01000000,  /** Drive 0 image is a D65, else a D81 */
  SDFDC_D1MD_MASK = 0b10000000,  /** Drive 1 image is a D65, else a D81 */
};

#ifdef __cplusplus
} // extern block
#endif

#endif // _SDCARD_H
