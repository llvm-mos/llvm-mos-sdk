// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MEGA65_H
#define _MEGA65_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wnested-anon-types"
#pragma clang diagnostic ignored "-Wgnu-binary-literal"
// -Wfixed-enum-extension does not exist in every clang this header is used
// with, and naming an absent group is itself a warning.
#pragma clang diagnostic ignored "-Wunknown-warning-option"
#pragma clang diagnostic ignored "-Wfixed-enum-extension"
#endif

#include <_45E100.h>
#include <_6526.h>
#include <_dmagic.h>
#include <_sdcard.h>
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
      uint8_t regx; // 0xD641
      /// Hypervisor Y register storage
      uint8_t regy; // 0xD642
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
#if defined(__mos__) && defined(__cplusplus)
static_assert(sizeof(struct __hypervisor) == 64);
#endif

/// Registers for the MEGA65 math accelerator
struct __cpu_math {
  union {
    uint8_t divout_fract8;  //!< Fractional part of MULTINA / MULTINB (0xD768)
    uint16_t divout_fract16;//!< Fractional part of MULTINA / MULTINB (0xD768)
    uint32_t divout_fract32;//!< Fractional part of MULTINA / MULTINB (0xD768)
  };
  union {
    uint8_t divout_whole8;  //!< Whole part of MULTINA / MULTINB (0xD76C)
    uint16_t divout_whole16;//!< Whole part of MULTINA / MULTINB (0xD76C)
    uint32_t divout_whole32;//!< Whole part of MULTINA / MULTINB (0xD76C)
  };
  union {
    uint8_t multina8;   //!< 8-bit Multiplier input A (0xD770)
    uint16_t multina16; //!< 16-bit Multiplier input A (0xD770)
    uint32_t multina32; //!< 32-bit Multiplier input A (0xD770)
  };
  union {
    uint8_t multinb8;   //!< 8-bit Multiplier input B (0xD774)
    uint16_t multinb16; //!< 16-bit Multiplier input B (0xD774)
    uint32_t multinb32; //!< 32-bit Multiplier input B (0xD774)
  };
  /// 64-bit product of MULTINA and MULTINB (0xD778)
  union {
    uint8_t multout8;
    uint16_t multout16;
    uint32_t multout32;
#ifdef __clang__
    uint64_t multout64;
#endif
    uint8_t multout[8];
  };
  uint32_t mathin[16]; //!< 32-bit programmable input (0xD780)
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

/// 6510/45GS02 CPU port bits. Bits 0-2 drive the C64-style banking; a bit
/// configured as an input in CPU_PORTDDR reads as 1, so clearing a ROM
/// requires the matching direction bit to be an output.
enum
#ifdef __clang__
    : uint8_t
#endif
{
  CPU_PORT_LORAM = 0b00000001,  ///< BASIC ROM at $A000-$BFFF
  CPU_PORT_HIRAM = 0b00000010,  ///< KERNAL ROM at $E000-$FFFF
  CPU_PORT_CHAREN = 0b00000100, ///< I/O at $D000-$DFFF, else character ROM
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
/// MEGA65 SD card controller
#define SDCARD (*(volatile struct __sdcard *)0xd680)
/// F011 floppy emulation: disk images and where they are
#define SDFDC (*(volatile struct __sdfdc *)0xd68a)
/// Ethernet controller
#define ETHERNET (*(volatile struct __45E100 *)0xd6e0)
/// DMAgic DMA controller
#define DMA (*(volatile struct DMAgicController *)0xd700)
/// Math busy flag
#define MATHBUSY (*(volatile uint8_t *)0xd70f)
/// Math accelerator
#define MATH (*(volatile struct __cpu_math *)0xd768)
/// The CIA 1
#define CIA1 (*(volatile struct __6526 *)0xdc00)
/// The CIA 2
#define CIA2 (*(volatile struct __6526 *)0xdd00)

/// Default color palette
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
  COLOR_DARKGREY = 0x0B,
  COLOR_MIDGREY = 0x0C,
  COLOR_LIGHTGREEN = 0x0D,
  COLOR_LIGHTBLUE = 0x0E,
  COLOR_LIGHTGREY = 0x0F,
  COLOR_GURUMEDITATION = 0x10,
  COLOR_RAMBUTAN = 0x11,
  COLOR_CARROT = 0x12,
  COLOR_LEMONTART = 0x13,
  COLOR_PANDAN = 0x14,
  COLOR_SEASICKGREEN = 0x15,
  COLOR_SOYLENTGREEN = 0x16,
  COLOR_SLIMERGREEN = 0x17,
  COLOR_THEOTHERCYAN = 0x18,
  COLOR_SEASKY = 0x19,
  COLOR_SMURFBLUE = 0x1A,
  COLOR_SCREENOFDEATH = 0x1B,
  COLOR_PLUMSAUCE = 0x1C,
  COLOR_SOURGRAPE = 0x1D,
  COLOR_BUBBLEGUM = 0x1E,
  COLOR_HOTTAMALES = 0x1F
};

// MEGA65 KERNAL function wrappers.

/// Return type for mega65_k_scrorg()
typedef struct {
  uint8_t max_col;  ///< Rightmost column index (79 in 80-column mode)
  uint8_t max_row;  ///< Bottom row index (24 for 25 rows)
  uint8_t addr_lo;  ///< Window top-left screen address, low byte
  uint8_t addr_hi;  ///< Window top-left screen address, high byte
  uint8_t is_40col; ///< 0=80 column mode, 1=40 column mode
} mega65_screen_info_t;

/// Return type for mega65_k_getio()
typedef struct {
  uint8_t input_dev;  ///< Current input device, 0 = keyboard
  uint8_t output_dev; ///< Current output device, 3 = screen
} mega65_io_t;

/// Return type for mega65_k_getlfs()
typedef struct {
  uint8_t la; ///< Logical file number
  uint8_t fa; ///< Device number
  uint8_t sa; ///< Secondary address, 0xFF if not set
} mega65_lfs_t;

/// Return type for mega65_k_plot_get()
typedef struct {
  uint8_t line; ///< Cursor line, 0-based
  uint8_t col;  ///< Cursor column, 0-based
} mega65_plot_t;

/// Return type for mega65_k_rdtim()
typedef struct {
  uint8_t hours;   ///< Hours 0-23 in BCD (e.g. 0x14 = 14)
  uint8_t minutes; ///< Minutes 0-59 in BCD (e.g. 0x30 = 30)
  uint8_t seconds; ///< Seconds 0-59 in BCD (e.g. 0x57 = 57)
  uint8_t tenths;  ///< Tenths of a second 0-9
} mega65_tod_t;

/// Add a PETSCII character to the keyboard input buffer.
/// The buffer is consumed by GETIN calls, not by the KERNAL IRQ.
///
/// @param petscii_char  PETSCII character code
/// @return 0 on success, 1 if the buffer is full
uint8_t mega65_k_addkey(unsigned char petscii_char) __attribute__((leaf));

/// Close all open files on the specified device.
/// Restores default I/O channels if the current channel was on that device.
///
/// @param device  Device number (0-31)
void mega65_k_close_all(uint8_t device) __attribute__((leaf));

/// Read the current input and output devices.
/// Modified by CHKIN and CKOUT.
///
/// @return input device (0=keyboard) and output device (3=screen)
mega65_io_t mega65_k_getio(void) __attribute__((leaf));

/// Read the current file parameters (logical address, device, secondary
/// address). Useful to determine the boot device before performing other disk
/// I/O.
///
/// @return logical file number, device number, and secondary address
///         (sa is 0xFF if not set)
mega65_lfs_t mega65_k_getlfs(void) __attribute__((leaf));

/// Search for a logical file number in use.
///
/// @param la  Logical file number to search for
/// @param fa  Pointer to receive device number (if found)
/// @param sa  Pointer to receive secondary address (if found)
/// @return 0 if found, 1 if not found
uint8_t mega65_k_lkupla(uint8_t la, uint8_t *fa, uint8_t *sa)
    __attribute__((leaf));

/// Search for a secondary address in use.
///
/// @param sa  Secondary address to search for
/// @param la  Pointer to receive logical file number (if found)
/// @param fa  Pointer to receive device number (if found)
/// @return 0 if found, 1 if not found
uint8_t mega65_k_lkupsa(uint8_t sa, uint8_t *la, uint8_t *fa)
    __attribute__((leaf));

/// Load or verify a file. Supports MEGA65 raw mode (flag bit 6).
/// flag: 0x00=load to address, 0x01=verify, 0x40=raw load, 0x41=raw verify.
/// Raw mode treats the first two bytes as data instead of a PRG header.
/// Requires SETBNK, SETLFS, SETNAM called first.
///
/// @param flag       Load flags (0=load, 1=verify, 0x40=raw load, 0x41=raw
/// verify)
/// @param load_addr  Destination address (used if SA=0; ignored if SA!=0)
/// @param end_addr   Pointer to receive end address+1 on success
/// @return 0 on success, or KERNAL error code (1-9)
uint8_t mega65_k_load(uint8_t flag, void *load_addr, void **end_addr)
    __attribute__((leaf));

/// Get cursor position relative to the active window.
///
/// @return cursor line and column, both 0-based
mega65_plot_t mega65_k_plot_get(void) __attribute__((leaf));

/// Set cursor position relative to the active window.
///
/// @param line  Cursor line (0-based)
/// @param col   Cursor column (0-based)
void mega65_k_plot_set(uint8_t line, uint8_t col) __attribute__((leaf));

/// Read the CIA1 time-of-day clock.
/// Returns hours, minutes, seconds (BCD), and tenths of a second.
/// This reads the CIA1 TOD, not the battery-backed RTC.
mega65_tod_t mega65_k_rdtim(void) __attribute__((leaf));

/// Get screen window size and properties (SCRORG).
/// The KERNAL reports the window as maximum indices, not counts, so a
/// full 80x25 screen comes back as max_col=79, max_row=24.
mega65_screen_info_t mega65_k_scrorg(void) __attribute__((leaf));

/// Set memory bank and filename bank for I/O operations (LOAD, SAVE, OPEN).
/// For simple bank mode (banks 0-5 in the first megabyte).
/// Must be called before LOAD, SAVE, or OPEN.
///
/// @param mem_bank Memory bank (0-5)
/// @param fn_bank  Filename bank (0-5)
void mega65_k_setbnk(uint8_t mem_bank, uint8_t fn_bank) __attribute__((leaf));

/// Set 28-bit memory and filename addresses for I/O operations.
/// For accessing addresses beyond the first megabyte.
/// The lower 16 bits of each address are set via other calls (SETNAM, LOAD).
///
/// @param mem_mb  Memory megabyte (bits 24-27, 0x0-0xF)
/// @param mem_hi  Memory address bits 16-23
/// @param fn_mb   Filename megabyte (bits 24-27, 0x0-0xF)
/// @param fn_hi   Filename address bits 16-23
void mega65_k_setbnk_28(uint8_t mem_mb, uint8_t mem_hi, uint8_t fn_mb,
                        uint8_t fn_hi) __attribute__((leaf));

/// Save memory to a file with optional raw mode (MEGA65 SAVEFL, $FF3B).
/// In raw mode, the two-byte PRG address header is omitted.
/// The memory region must fit within a single bank.
/// Requires SETBNK, SETLFS, SETNAM called first.
///
/// @param start_addr       Start of memory region to save
/// @param end_addr_plus1   End address + 1 (first byte NOT saved)
/// @param raw              true for raw mode (omit PRG header)
/// @return 0 on success, or KERNAL error code (1-9)
uint8_t mega65_k_savefl(const void *start_addr, const void *end_addr_plus1,
                        bool raw) __attribute__((leaf));

/// Enable or disable KERNAL messages (LOADING, SAVING, I/O ERROR).
/// These are disabled by default.
///
/// @param mode  Bit 7 = control messages, bit 6 = error messages
void mega65_k_setmsg(uint8_t mode) __attribute__((leaf));

/// Set the CIA1 time-of-day clock.
/// All values are in BCD format (e.g. 0x59 = 59 decimal).
/// This sets the CIA1 TOD, not the battery-backed RTC.
///
/// @param hours    Hours 0-23 in BCD
/// @param minutes  Minutes 0-59 in BCD
/// @param seconds  Seconds 0-59 in BCD
/// @param tenths   Tenths of a second 0-9
void mega65_k_settim(uint8_t hours, uint8_t minutes, uint8_t seconds,
                     uint8_t tenths) __attribute__((leaf));

/// Keyboard lock bits, read and written by mega65_k_sysflags_get/_set.
/// Bits 0-3 are reserved and must be zero.
enum
#ifdef __clang__
    : uint8_t
#endif
{
  MEGA65_LOCK_GO64 = 0b00010000,       ///< GO64 command locked out
  MEGA65_LOCK_RAW_FKEYS = 0b00100000,  ///< Function keys give raw keys
  MEGA65_LOCK_NO_SCROLL = 0b01000000,  ///< No-Scroll key locked out
  MEGA65_LOCK_MEGA_SHIFT = 0b10000000, ///< MEGA+Shift charset toggle locked out
};

/// Read the keyboard lock bits (SYSFLAGS).
///
/// @return the MEGA65_LOCK_* bits currently set
uint8_t mega65_k_sysflags_get(void) __attribute__((leaf));

/// Set the keyboard lock bits (SYSFLAGS).
///
/// @param locks  MEGA65_LOCK_* bits to apply
void mega65_k_sysflags_set(uint8_t locks) __attribute__((leaf));

/// Toggle between 40x25 and 80x25 text modes.
void mega65_k_swapper(void) __attribute__((leaf));

/// Read a byte from an address in any MEGA65 bank via KERNAL LDA_FAR ($FF74).
/// Uses 32-bit flat addressing internally; does not change the memory map.
/// Equivalent to lda (addr),y in the given bank.
///
/// @param bank      MEGA65 64K bank number (0-5)
/// @param addr      Base address within the bank
/// @param y_offset  Index added to addr
/// @return Byte value at bank:addr+y_offset
uint8_t mega65_k_lda_far(uint8_t bank, uint16_t addr, uint8_t y_offset)
    __attribute__((leaf));

/// Store a byte to an address in any MEGA65 bank via KERNAL STA_FAR ($FF77).
/// Uses 32-bit flat addressing internally; does not change the memory map.
/// Equivalent to sta (addr),y in the given bank.
///
/// @param bank      MEGA65 64K bank number (0-5)
/// @param addr      Base address within the bank
/// @param y_offset  Index added to addr
/// @param value     Byte to store
void mega65_k_sta_far(uint8_t bank, uint16_t addr, uint8_t y_offset,
                      uint8_t value) __attribute__((leaf));

/// Compare a byte with an address in any MEGA65 bank via KERNAL CMP_FAR
/// ($FF7A). Uses 32-bit flat addressing internally; does not change the memory
/// map. Equivalent to cmp (addr),y in the given bank.
///
/// @param bank      MEGA65 64K bank number (0-5)
/// @param addr      Base address within the bank
/// @param y_offset  Index added to addr
/// @param value     Byte to compare against
/// @return 0 if equal, 1 if not equal
uint8_t mega65_k_cmp_far(uint8_t bank, uint16_t addr, uint8_t y_offset,
                         uint8_t value) __attribute__((leaf));

// Hyppo hypervisor service wrappers. These operate on the SD card FAT
// filesystem directly, bypassing the KERNAL and D81 disk images, and are safe
// to use with banking.
//
// Trap convention: LDA #value : STA $D640 : CLV. The CLV is a mandatory
// filler -- the byte after the STA may be consumed by the trap return, so it
// must not be an instruction that matters.
// Success: C=1. Error: C=0, error code in A.

/// Hyppo hypervisor error codes.
/// Functions return MEGA65_H_OK (0) on success, or an error code on failure.
typedef enum
#ifdef __clang__
    : uint8_t
#endif
{ MEGA65_H_OK = 0x00,                     ///< Success
  MEGA65_H_ERR_PARTITION = 0x01,          ///< Partition type not supported
  MEGA65_H_ERR_BAD_SIGNATURE = 0x02,      ///< Missing/incorrect signature
  MEGA65_H_ERR_SMALL_FAT = 0x03,          ///< FAT12/FAT16 not supported
  MEGA65_H_ERR_TOO_MANY_RESERVED = 0x04,  ///< >65535 reserved sectors
  MEGA65_H_ERR_NOT_TWO_FATS = 0x05,       ///< Partition lacks two FAT copies
  MEGA65_H_ERR_TOO_FEW_CLUSTERS = 0x06,   ///< Too few clusters
  MEGA65_H_ERR_READ_TIMEOUT = 0x07,       ///< SD card read timeout
  MEGA65_H_ERR_PARTITION_ERROR = 0x08,    ///< Unspecified partition error
  MEGA65_H_ERR_INVALID_ADDRESS = 0x10,    ///< Invalid address argument
  MEGA65_H_ERR_ILLEGAL_VALUE = 0x11,      ///< Illegal value argument
  MEGA65_H_ERR_READ_ERROR = 0x20,         ///< Unspecified read error
  MEGA65_H_ERR_WRITE_ERROR = 0x21,        ///< Unspecified write error
  MEGA65_H_ERR_NO_SUCH_DRIVE = 0x80,      ///< Drive number does not exist
  MEGA65_H_ERR_NAME_TOO_LONG = 0x81,      ///< Filename >63 characters
  MEGA65_H_ERR_NOT_IMPLEMENTED = 0x82,    ///< Service not implemented
  MEGA65_H_ERR_FILE_TOO_LONG = 0x83,      ///< File >16MB
  MEGA65_H_ERR_TOO_MANY_OPEN = 0x84,      ///< All file descriptors in use
  MEGA65_H_ERR_INVALID_CLUSTER = 0x85,    ///< Invalid cluster number
  MEGA65_H_ERR_IS_DIRECTORY = 0x86,       ///< Expected file, got directory
  MEGA65_H_ERR_NOT_DIRECTORY = 0x87,      ///< Expected directory, got file
  MEGA65_H_ERR_FILE_NOT_FOUND = 0x88,     ///< File not found
  MEGA65_H_ERR_INVALID_FD = 0x89,         ///< Invalid file descriptor
  MEGA65_H_ERR_IMAGE_WRONG_LENGTH = 0x8A, ///< Disk image wrong size
  MEGA65_H_ERR_IMAGE_FRAGMENTED = 0x8B,   ///< Disk image not contiguous
  MEGA65_H_ERR_NO_SPACE = 0x8C,           ///< No free space on SD card
  MEGA65_H_ERR_FILE_EXISTS = 0x8D,        ///< File already exists
  MEGA65_H_ERR_DIRECTORY_FULL = 0x8E,     ///< Directory full
  MEGA65_H_ERR_DOUBLE_ATTACH = 0x8F,      ///< Image already attached
  MEGA65_H_EOF = 0xFF,                    ///< End of file/directory
} mega65_h_err;

/// FAT directory entry returned by mega65_h_readdir().
/// Total size: 87 bytes. Buffer must be 256-byte aligned.
typedef struct {
  char long_name[64];     ///< Long filename, null-terminated (max 63 chars)
  uint8_t name_len;       ///< Length of long filename
  char short_name[11];    ///< 8.3 filename (space-padded, no dot/null)
  uint8_t _reserved[2];   ///< Reserved
  uint32_t start_cluster; ///< Starting cluster number
  uint32_t file_size;     ///< File size in bytes
  uint8_t attributes;     ///< Attribute flags (MEGA65_H_ATTR_*)
} mega65_h_dirent;

/// File attribute flags for mega65_h_dirent.attributes.
enum
#ifdef __clang__
    : uint8_t
#endif
{
  MEGA65_H_ATTR_READONLY = 0x01, ///< Read-only file
  MEGA65_H_ATTR_HIDDEN = 0x02,   ///< Hidden file
  MEGA65_H_ATTR_SYSTEM = 0x04,   ///< System file
  MEGA65_H_ATTR_VOLLABEL = 0x08, ///< Volume label
  MEGA65_H_ATTR_SUBDIR = 0x10,   ///< Sub-directory
  MEGA65_H_ATTR_ARCHIVE = 0x20,  ///< Archive flag
};

/// Hyppo/HDOS version information returned by mega65_h_getversion().
typedef struct {
  uint8_t hyppo_major; ///< Hyppo version major
  uint8_t hyppo_minor; ///< Hyppo version minor
  uint8_t hdos_major;  ///< HDOS version major
  uint8_t hdos_minor;  ///< HDOS version minor
} mega65_h_version;

/// Flags for mega65_h_attach().
enum
#ifdef __clang__
    : uint8_t
#endif
{
  MEGA65_H_ATTACH_D0 = 0x00,  ///< Attach to drive 0
  MEGA65_H_ATTACH_D1 = 0x01,  ///< Attach to drive 1
  MEGA65_H_DETACH_D0 = 0x80,  ///< Detach drive 0
  MEGA65_H_DETACH_D1 = 0x81,  ///< Detach drive 1
  MEGA65_H_DETACH_ALL = 0xC2, ///< Detach both drives
};

// --- System services ---

/// Get Hyppo and HDOS version numbers.
///
/// @return Hyppo and HDOS major/minor versions
mega65_h_version mega65_h_getversion(void) __attribute__((leaf));

/// Get the error code from the last failed Hyppo service call.
/// Only valid if the previous call returned a nonzero error.
///
/// @return Error code from the last failed service
mega65_h_err mega65_h_geterrorcode(void) __attribute__((leaf));

// --- Drive services ---

/// Get the currently selected SD card drive number.
///
/// @return Current drive number
uint8_t mega65_h_getcurrentdrive(void) __attribute__((leaf));

/// Get the default SD card drive number (set at boot).
///
/// @return Default drive number
uint8_t mega65_h_getdefaultdrive(void) __attribute__((leaf));

/// Select the active SD card drive/partition.
///
/// @param drive  Drive number
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_selectdrive(uint8_t drive) __attribute__((leaf));

// --- Filename and file search ---

/// Set the Hyppo filename for subsequent find/load operations.
/// Filename is ASCII (not PETSCII), null-terminated, max 63 characters.
///
/// Staged in the page the linker script gives as __mega65_h_name_buf, which
/// this platform's script puts at $0100 -- the bottom of the hardware stack,
/// far below where compiled code reaches. Move it with
///
///   -Wl,--defsym=__mega65_h_name_buf=0x0400
///
/// @param filename  ASCII filename string
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_setname(const char *filename) __attribute__((leaf));

/// Name a filename buffer the caller has already filled in.
///
/// Hyppo copies a whole page and reads only its high byte, so a buffer is
/// named by page. Use this when the program owns the page: two names at once
/// need two pages, and a program loading a file over itself needs the name to
/// outlive the page it came from.
///
/// @param page  High byte of a page-aligned 256-byte buffer below $7F00,
///              holding the null-terminated ASCII name
/// @return MEGA65_H_OK, or MEGA65_H_ERR_INVALID_ADDRESS for a page at or
///         above $7F
mega65_h_err mega65_h_setname_page(uint8_t page) __attribute__((leaf));

/*** Freeze-slot services (syspart trap $D642) ***/

/// These use $D642, the system-partition trap, where every other mega65_h_
/// function here uses $D640. All of them need a system partition on the SD
/// card; without one, the machine reports no slots.

/// First sector of a freeze slot.
///
/// Check the slot against mega65_h_get_freeze_slot_count() first. Hyppo's own
/// range check does not work, and this trap cannot report a bad slot.
///
/// @param slot  Freeze slot number
/// @return Sector number, or anything at all if the slot is out of range
uint32_t mega65_h_locate_freezeslot(uint16_t slot) __attribute__((leaf));

/// Replace the running program with the one held in a freeze slot.
///
/// Control does not come back if this succeeds: hyppo restores the frozen
/// program over this one, so code after the call runs only on failure.
///
/// Hyppo restores only X on entry to this trap, because its own dispatch
/// clobbers X and leaves Y alone: the low byte reaches it in Y untouched.
///
/// @param slot  Freeze slot number
void mega65_h_unfreeze_from_slot(uint16_t slot) __attribute__((leaf));

/// Copy hyppo's list of memory regions a freeze covers.
///
/// @param dest  Buffer below $8000; a higher address quietly lands 32KB
///              lower instead of being refused
/// @return MEGA65_H_OK
mega65_h_err mega65_h_read_freeze_region_list(void *dest) __attribute__((leaf));

/// Number of freeze slots the system partition holds.
///
/// @return Slot count, or 0 if there is no system partition
uint16_t mega65_h_get_freeze_slot_count(void) __attribute__((leaf));

/// Copy the running program's 256-byte task descriptor into a page.
///
/// Says which disk images are mounted, among other task state. Hyppo copies
/// a whole page, so the buffer is named by page.
///
/// @param page  High byte of a page-aligned 256-byte buffer below $7F00
/// @return MEGA65_H_OK, or MEGA65_H_ERR_INVALID_ADDRESS for a page at or
///         above $7F
mega65_h_err mega65_h_get_proc_desc(uint8_t page) __attribute__((leaf));

/// Find a file by name in the current directory.
/// Precondition: mega65_h_setname() called with the target filename.
/// On success, the internal FAT directory entry is set for use by
/// mega65_h_openfile(), mega65_h_chdir(), or mega65_h_rmfile().
///
/// @return MEGA65_H_OK or error code (MEGA65_H_ERR_FILE_NOT_FOUND)
mega65_h_err mega65_h_findfile(void) __attribute__((leaf));

/// Begin searching for files matching the name set by mega65_h_setname().
/// Returns a directory file descriptor for use with mega65_h_findnext().
/// Caller must close with mega65_h_closedir() unless findnext exhausts
/// the search (auto-closes on MEGA65_H_ERR_FILE_NOT_FOUND).
///
/// @param fd  Pointer to receive the directory file descriptor
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_findfirst(uint8_t *fd) __attribute__((leaf));

/// Find the next matching file after mega65_h_findfirst().
/// Auto-closes the fd on MEGA65_H_ERR_FILE_NOT_FOUND.
///
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_findnext(void) __attribute__((leaf));

// --- File I/O ---
// readfile/writefile operate on the "current file" set by openfile.
// Data is transferred via the Hyppo sector buffer at $FFD6E00-$FFD6FFF.
// Use DMA or 32-bit addressing to access the sector buffer.

/// Open a file for reading/writing.
/// Precondition: file found via findfile/findfirst/findnext/readdir.
/// Sets the file as the "current file" for readfile/writefile.
///
/// Acts on the dirent left by the last search. A search that matched nothing
/// does not clear that dirent, so this still succeeds and reopens the file
/// found before it — check the search result yourself.
///
/// @param fd  Pointer to receive the file descriptor (for closefile)
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_openfile(uint8_t *fd) __attribute__((leaf));

/// Hyppo's 512-byte sector buffer, which readfile and writefile transfer
/// through. A 28-bit address: reach it with DMA or 32-bit addressing, not an
/// ordinary pointer.
#define MEGA65_H_SECTOR_BUFFER 0xFFD6E00UL

/// Read the next sector of the current file into MEGA65_H_SECTOR_BUFFER.
/// End of file gives MEGA65_H_OK with a count of 0, and *count is always
/// written, so a loop can rely on it.
///
/// @param count  Pointer to receive bytes read (0 = EOF)
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_readfile(uint16_t *count) __attribute__((leaf));

/// Write the sector buffer to the current file (WRITEFILE).
/// The file must have been created by mega65_h_mkfile() and opened.
/// *count is written on every path, so it is safe to loop on.
///
/// @param count  Pointer to receive bytes written
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_writefile(uint16_t *count) __attribute__((leaf));

/// Create a file of the given size (MKFILE), named by mega65_h_setname().
/// Hyppo's limitations, not this wrapper's: 8.3 names only, current directory
/// only, space allocated contiguously so the file can be mounted as an image,
/// 16 MB ceiling, and a filesystem without room is not reported cleanly.
///
/// @param size  File size in bytes, up to 16 MB
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_mkfile(uint32_t size) __attribute__((leaf));

/// Allow writes to the attached D81 image (D81WRITE_EN).
/// Attaching with mega65_h_attach() alone leaves the image read-only.
///
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_d81write_en(void) __attribute__((leaf));

/// Close a file descriptor.
///
/// @param fd  File descriptor from mega65_h_openfile()
void mega65_h_closefile(uint8_t fd) __attribute__((leaf));

/// Close all open file and directory descriptors.
void mega65_h_closeall(void) __attribute__((leaf));

/// Delete a file.
/// Precondition: file found via findfile/findfirst/findnext/readdir.
///
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_rmfile(void) __attribute__((leaf));

// --- Directory I/O ---

/// Open the current working directory for reading.
///
/// @param fd  Pointer to receive the directory file descriptor
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_opendir(uint8_t *fd) __attribute__((leaf));

/// Read the next directory entry.
/// dest must be 256-byte aligned and below $7F00: Hyppo takes only a page
/// number and rejects pages $7F and above, so a buffer the linker happened to
/// place higher fails at run time with MEGA65_H_ERR_INVALID_ADDRESS.
/// Returns MEGA65_H_EOF when no more entries remain.
///
/// @param fd    Directory file descriptor from mega65_h_opendir()
/// @param dest  Page-aligned buffer to receive the FAT directory entry
/// @return MEGA65_H_OK, MEGA65_H_EOF, or error code
mega65_h_err mega65_h_readdir(uint8_t fd, mega65_h_dirent *dest)
    __attribute__((leaf));

/// Close a directory file descriptor.
///
/// @param fd  File descriptor from mega65_h_opendir()
void mega65_h_closedir(uint8_t fd) __attribute__((leaf));

/// Change to a subdirectory.
/// Precondition: directory found via findfile/findfirst/findnext/readdir.
/// Use ".." entry to go up one level.
///
/// @return MEGA65_H_OK or error code (MEGA65_H_ERR_NOT_DIRECTORY)
mega65_h_err mega65_h_chdir(void) __attribute__((leaf));

/// Change to the root directory of a drive.
///
/// @param drive  Drive number
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_cdrootdir(uint8_t drive) __attribute__((leaf));

// --- File loading (bypasses sector buffer) ---

/// Load a file from the SD card into chip memory at a 28-bit address.
/// Call mega65_h_setname() first. Loads the entire file at once.
///
/// @param addr  28-bit destination in chip memory ($000000-$FFFFFF)
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_loadfile(uint32_t addr) __attribute__((leaf));

/// Load a file from the SD card into attic/hyper RAM.
/// Call mega65_h_setname() first. Loads the entire file at once.
///
/// @param addr  24-bit offset in attic RAM (base $08000000 added by hardware)
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_loadfile_attic(uint32_t addr) __attribute__((leaf));

// --- Disk image services ---

/// Attach or detach a D81 disk image to an F011 floppy drive.
/// For attach: call mega65_h_setname() with the image filename first.
/// flags: MEGA65_H_ATTACH_D0, MEGA65_H_ATTACH_D1, MEGA65_H_DETACH_D0,
///        MEGA65_H_DETACH_D1, MEGA65_H_DETACH_ALL.
///
/// @param flags  Attach/detach flags
/// @return MEGA65_H_OK or error code
mega65_h_err mega65_h_attach(uint8_t flags) __attribute__((leaf));

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef __cplusplus
} // extern block
#endif
#endif // _MEGA65_H
