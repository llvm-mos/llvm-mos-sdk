// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _VIC4_H
#define _VIC4_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __vic4 {
  union {
    struct {
      uint8_t spr0_x; //!< Sprite 0, X coordinate (offset 0x00)
      uint8_t spr0_y; //!< Sprite 0, Y coordinate (offset 0x01)
      uint8_t spr1_x; //!< Sprite 1, X coordinate (offset 0x02)
      uint8_t spr1_y; //!< Sprite 1, Y coordinate (offset 0x03)
      uint8_t spr2_x; //!< Sprite 2, X coordinate (offset 0x04)
      uint8_t spr2_y; //!< Sprite 2, Y coordinate (offset 0x05)
      uint8_t spr3_x; //!< Sprite 3, X coordinate (offset 0x06)
      uint8_t spr3_y; //!< Sprite 3, Y coordinate (offset 0x07)
      uint8_t spr4_x; //!< Sprite 4, X coordinate (offset 0x08)
      uint8_t spr4_y; //!< Sprite 4, Y coordinate (offset 0x09)
      uint8_t spr5_x; //!< Sprite 5, X coordinate (offset 0x0A)
      uint8_t spr5_y; //!< Sprite 5, Y coordinate (offset 0x0B)
      uint8_t spr6_x; //!< Sprite 6, X coordinate (offset 0x0C)
      uint8_t spr6_y; //!< Sprite 6, Y coordinate (offset 0x0D)
      uint8_t spr7_x; //!< Sprite 7, X coordinate (offset 0x0E)
      uint8_t spr7_y; //!< Sprite 7, Y coordinate (offset 0x0F)
    };
    struct {
      uint8_t x; //!< x coordinate
      uint8_t y; //!< y coordinate
    } spr_pos[8];
  };
  uint8_t spr_hi_x;   //!< High bits of X coordinate (offset 0x10)
  uint8_t ctrl1;      //!< Control register 1 (offset 0x11)
  uint8_t rasterline; //!< Current raster line (offset 0x12)
  union {
    struct {
      uint8_t strobe_x; //!< Light pen, X position (offset 0x13)
      uint8_t strobe_y; //!< Light pen, Y position (offset 0x14)
    };
    struct {
      uint8_t x; //!< Light pen, X position (offset 0x13)
      uint8_t y; //!< Light pen, Y position (offset 0x14)
    } strobe;
  };
  uint8_t spr_ena;     //!< Enable sprites (offset 0x15)
  uint8_t ctrl2;       //!< Control register 2 (offset 0x16)
  uint8_t spr_exp_y;   //!< Expand sprites in Y dir (offset 0x17)
  uint8_t addr;        //!< Address of chargen and video ram (offset 0x18)
  uint8_t irr;         //!< Interrupt request register (offset 0x19)
  uint8_t imr;         //!< Interrupt mask register (offset 0x1A)
  uint8_t spr_bg_prio; //!< Priority to background (offset 0x1B)
  uint8_t spr_mcolor;  //!< Sprite multicolor bits (offset 0x1C)
  uint8_t spr_exp_x;   //!< Expand sprites in X dir (offset 0x1D)
  uint8_t spr_coll;    //!< Sprite/sprite collision reg (offset 0x1E)
  uint8_t spr_bg_coll; //!< Sprite/background collision reg (offset 0x1F)
  uint8_t bordercol;   //!< Border colour (256 colour) (offset 0x20)
  uint8_t screencol;   //!< Screen colour (256 colour) (offset 0x21)
  union {
    struct {
      uint8_t mcolor1; //!< Multi-colour 1 (256 colour) (offset 0x22)
      uint8_t mcolor2; //!< Multi-colour 2 (256 colour) (offset 0x23)
      uint8_t mcolor3; //!< Multi-colour 3 (256 colour) (offset 0x24)
    };
    uint8_t mcolor[3]; //!< Multi-colour 1-3 (256 colour) (offset 0x22)
  };
  union {
    struct {
      /// Sprite multi-colour 0 (8-bit for selection of any palette
      /// colour) (offset 0x25)
      uint8_t spr_mcolor0;
      /// Sprite multi-colour 1 (8-bit for selection of any palette
      /// colour) (offset 0x26)
      uint8_t spr_mcolor1;
    };
    /// Sprite multi-colour 0-1 (8-bit for selection of any palette
    /// colour) (offset 0x25)
    uint8_t spr_mcolors[2]; //!< Color for multicolor sprites
  };
  union {
    /// Sprite N colour / 16-colour sprite transparency colour (lower
    /// nybl) (offset 0x27)
    struct {
      uint8_t spr0_color; //!< Color sprite 0 (offset 0x27)
      uint8_t spr1_color; //!< Color sprite 1 (offset 0x28)
      uint8_t spr2_color; //!< Color sprite 2 (offset 0x29)
      uint8_t spr3_color; //!< Color sprite 3 (offset 0x2A)
      uint8_t spr4_color; //!< Color sprite 4 (offset 0x2B)
      uint8_t spr5_color; //!< Color sprite 5 (offset 0x2C)
      uint8_t spr6_color; //!< Color sprite 6 (offset 0x2D)
      uint8_t spr7_color; //!< Color sprite 7 (offset 0x2E)
    };
    /// Sprite N colour / 16-colour sprite transparency colour (lower
    /// nybl) (offset 0x27)
    uint8_t spr_color[8];
  };
  /// KEY register (offset 0x2f)
  uint8_t key;
  /// VIC-III Control Register A (ROM banks) (offset 0x30)
  uint8_t ctrla;
  /// VIC-III Control Register B (offset 0x31)
  uint8_t ctrlb;
  /// Unused (offset 0x32)
  uint8_t unused;

  union {
    struct {
      uint8_t b0_addr; //!< Bitplane 0 Address (offset 0x33)
      uint8_t b1_addr; //!< Bitplane 1 Address (offset 0x34)
      uint8_t b2_addr; //!< Bitplane 2 Address (offset 0x35)
      uint8_t b3_addr; //!< Bitplane 3 Address (offset 0x36)
      uint8_t b4_addr; //!< Bitplane 4 Address (offset 0x37)
      uint8_t b5_addr; //!< Bitplane 5 Address (offset 0x38)
      uint8_t b6_addr; //!< Bitplane 6 Address (offset 0x39)
      uint8_t b7_addr; //!< Bitplane 7 Address (offset 0x3A)
    };
    uint8_t bn_addr[8]; //!< Bitplane addresses (0-7) (offset 0x33)
  };

  /// Complement bitplane flags (offset 0x3B)
  uint8_t bpcomp;
  /// Bitplane X (offset 0x3C)
  uint8_t bpx;
  /// Bitplane Y (offset 0x3D)
  uint8_t bpy;
  /// Bitplane X Offset (offset 0x3E)
  uint8_t hpos;
  /// Bitplane Y Offset (offset 0x3F)
  uint8_t vpos;
  union {
    struct {
      /// Display Address Translater (DAT) Bitplane 0 port (offset 0x40)
      uint8_t b0pix;
      /// Display Address Translater (DAT) Bitplane 1 port (offset 0x41)
      uint8_t b1pix;
      /// Display Address Translater (DAT) Bitplane 2 port (offset 0x42)
      uint8_t b2pix;
      /// Display Address Translater (DAT) Bitplane 3 port (offset 0x43)
      uint8_t b3pix;
      /// Display Address Translater (DAT) Bitplane 4 port (offset 0x44)
      uint8_t b4pix;
      /// Display Address Translater (DAT) Bitplane 5 port (offset 0x45)
      uint8_t b5pix;
      /// Display Address Translater (DAT) Bitplane 6 port (offset 0x46)
      uint8_t b6pix;
      /// Display Address Translater (DAT) Bitplane 7 port (offset 0x47)
      uint8_t b7pix;
    };
    /// Display Address Translater (DAT) Bitplane N ports (offset 0x40)
    uint8_t bnpix[8];
  };
  union {
    /// Top border position (low byte) (offset 0x48)
    uint16_t tbdrpos;
    struct {
      /// Top border position (low byte) (offset 0x48)
      uint8_t tbdrpos_lsb;
      /// Top border position MSB and sprite bitplane-modify-mode enables
      /// (offset 0x49)
      uint8_t tbdrpos_msb;
    };
  };
  union {
    /// Bottom border position (offset 0x4A-0x4B)
    uint16_t bbdrpos;
    struct {
      /// Bottom border position, low byte (offset 0x4A)
      uint8_t bbdrpos_lsb;
      /// Bottom border position and sprite bitplane-modify-mode enables (offset
      /// 0x4B)
      uint8_t bbdrpos_msb;
    };
  };
  /// Character generator horizontal position (low byte) (offset 0x4C)
  uint8_t textxpos_lsb;
  /// Character generator horizontal position and sprite horizontal tile enables
  /// (offser 0x4D)
  uint8_t textxpos_msb;
  /// Character generator vertical position (low byte) (offset 0x4E)
  uint8_t textypos_lsb;
  /// Character generator vertical position and sprite
  /// horizontal tile enables (offset 0x4F)
  uint8_t textypos_msb;
  /// Read horizontal raster scan position (lower byte) (offset 0x50)
  uint8_t xpos_lsb;
  /// Read horizontal raster scan position (high byte) (offset 0x51)
  uint8_t xpos_msb;
  /// Read physical raster position (low byte) (offset 0x52)
  uint8_t fn_raster_lsb;
  /// Read physical raster position (high bits) (offset 0x53)
  uint8_t fn_raster_msb;
  /// VIC-IV Control register C (0x54)
  uint8_t ctrlc;
  /// sprite extended height enable (one bit per sprite) (offset
  /// 0x55)
  uint8_t spr_hgten;
  /// Sprite extended height size (sprite pixels high) (offset 0x56)
  uint8_t spr_hght;
  /// Sprite extended width enables (offset 0x57)
  uint8_t spr_x64en;
  /// Characters per logical text row (offset 0x58-0x59)
  uint16_t linestep;
  /// Horizontal hardware scale of text mode (pixel 120ths per
  /// pixel) (offset 0x5A)
  uint8_t chrxscl;
  /// Vertical scaling of text mode (number of physical rasters
  /// per char text row) (offset 0x5B)
  uint8_t chryscl;
  union {
    /// Width of single side border (offset 0x5C-0x5D)
    uint16_t sdbdrwd;
    struct {
      /// Width of single side border (offset 0x5C)
      uint8_t sdbdrwd_lsb;
      /// Side border width (offset 0x5D)
      uint8_t sdbdrwd_msb;
    };
  };
  /// Number of characters to display per row, LSB (offset: 0x5E)
  uint8_t chrcount;
  /// Sprite H640 X Super-MSBs (offset 0x5F)
  uint8_t spr_xsmsbs;
  union {
    /// Screen RAM precise base address (24 bit address) (offset 0x60)
    uint32_t scrnptr;
    struct {
      uint8_t scrnptr_lsb; //!< Screen RAM precise base address (bits 0 - 7)
                           //!< (offset 0x60)
      uint8_t scrnptr_msb; //!< Screen RAM precise base address (bits 15 - 8)
                           //!< (offset 0x61)
      uint8_t scrnptr_bnk; //!! screen RAM precise base address (bits 23 - 16)
                           //!(offset 0x62)
      /// Screen RAM precise base address (bits 31 - 24) (offset 0x63)
      /// CHRCOUNT Number of characters to display per.
      /// EXGLYPH source full-colour character data from expansion RAM.
      uint8_t scrnptr_mb;
    };
  };
  /// Colour RAM base address (offset 0x64)
  uint16_t colptr;
  /// Debug (offset 0x66)
  uint8_t debug1;
  /// Sprite/bitplane first X (DEBUG WILL BE REMOVED) (offset 0x67)
  uint8_t sbpdebug;
  union {
    /// Character set precise base address (24 bit address) (offset 0x68)
    uint32_t charptr;
    struct {
      /// Character set precise base address (bits 0 - 7)
      uint8_t charptr_lsb;
      /// Character set precise base address (bits 15 - 8)
      uint8_t charptr_msb;
      /// Character set precise base address (bits 23 - 16)
      uint8_t charptr_bnk;
      /// Sprite 16-colour mode enables
      uint8_t spr_16en;
    };
  };
  union {
    /// Sprite pointer address (24 bit address) (offset 0x6C)
    uint32_t spr_ptradr;
    struct {
      /// Sprite pointer address (bits 7 - 0)
      uint8_t spr_ptradr_lsb;
      /// Sprite pointer address (bits 15 - 8)
      uint8_t spr_ptradr_msb;
      /// Sprite pointer address (bits 22 - 16)
      uint8_t spr_ptradr_bnk;
      /// First VIC-II raster line (offset 0x6F)
      uint8_t rasline0;
    };
  };
  /// VIC-IV palette bank selection (offset 0x70)
  uint8_t palsel;
  /// VIC-IV 16-colour bitplane enable flags (offset 0x71)
  uint8_t bp16ens;
  /// Sprite Y position adjustment (offset 0x72)
  uint8_t spr_yadj;
  /// Alpha delay and raster height (offset 0x73)
  uint8_t alphadelay;
  /// Sprite alpha-blend enable (offset 0x74)
  uint8_t spr_enalpha;
  /// Sprite alpha-blend value (offset 0x75)
  uint8_t spr_alphaval;
  /// Sprite V400 enables (offset 0x76)
  uint8_t spr_env400;
  /// Sprite V400 Y position MSBs (offset 0x77)
  uint8_t spr_ymsbs;
  /// Sprite V400 Y position super MSBs (offset 0x78)
  uint8_t spr_ysmsbs;
  /// Raster compare value (offset 0x79)
  uint8_t rstcmp;
  /// Raster compare value MSB (offset 0x7A)
  uint8_t rstcmp_msb;
  /// Number of text rows to display (offset 0x7B)
  uint8_t disp_rows;
  /// hsync/vsync polarity (offset 0x7C)
  uint8_t syncpol;
  /// VIC-IV debug X position (LSB) (offset 0x7D)
  uint8_t debugx;
  /// VIC-IV debug Y position (LSB) (offset 0x7E)
  uint8_t debugy;
  /// VIC-IV debug X/Y position (MSB) (offset 0x7F)
  uint8_t debugxy;
};

#ifdef __cplusplus
static_assert(sizeof(__vic4) == 0x80);
#endif

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
  /** display border colour (256 colour) */
  VIC4_BORDERCOL_MASK = 0b11111111,
  /** screen colour (256 colour) */
  VIC4_SCREENCOL_MASK = 0b11111111,
  /** multi-colour 1 (256 colour) */
  VIC4_MC1_MASK = 0b11111111,
  /** multi-colour 2 (256 colour) */
  VIC4_MC2_MASK = 0b11111111,
  /** multi-colour 3 (256 colour) */
  VIC4_MC3_MASK = 0b11111111,
  /** top border position MSB */
  VIC4_TBDRPOS_MASK = 0b00001111,
  /** Sprite bitplane-modify-mode enables */
  VIC4_SPRBPMEN_MASK = 0b11110000,
  /** bottom border position */
  VIC4_BBDRPOS_MASK = 0b00001111,
  /** Sprite bitplane-modify-mode enables */
  GS_VIC4_SPRBPMEN_MASK = 0b11110000,
  /** character generator horizontal position */
  VIC4_TEXTXPOS_MASK = 0b00001111,
  /** Sprite horizontal tile enables. */
  VIC4_SPRTILEN_MASK = 0b11110000,
  /** Character generator vertical position */
  VIC4_TEXTYPOS_MASK = 0b00001111,
  /** Sprite 7-4 horizontal tile enables */
  GS_VIC4_SPRTILEN_MASK = 0b11110000,
  /** Read horizontal raster scan position MSB */
  VIC4_XPOSMSB_MASK = 0b00111111,
  /** When set, the Raster Rewrite Buffer is only updated every 2nd raster line,
   * limiting resolution to V200, but allowing more cycles for Raster-Rewrite
   * actions. */
  VIC4_DBLRR_MASK = 0b01000000,
  /** When clear, raster rewrite double buffering is used */
  VIC4_NORRDEL_MASK = 0b10000000,
  /** Read physical raster position */
  VIC4_FN_RASTER_MSB_MASK = 0b00000111,
  /** Enable simulated shadow-mask (PALEMU must also be enabled) */
  VIC4_SHDEMU_MASK = 0b01000000,
  /** Read raster compare source (0=VIC-IV fine raster, 1=VIC-II raster),
   * provides same value as set in FNRSTCMP */
  VIC4_FNRST_MASK = 0b10000000,
  /** enable 16-bit character numbers (two screen bytes per character)
   */
  VIC4_CHR16_MASK = 0b00000001,
  /** enable full-colour mode for character numbers <=$FF */
  VIC4_FCLRLO_MASK = 0b00000010,
  /** enable full-colour mode for character numbers >$FF */
  VIC4_FCLRHI_MASK = 0b00000100,
  /** video output horizontal smoothing enable */
  VIC4_SMTH_MASK = 0b00001000,
  /** Sprite H640 enable */
  VIC4_SPR_H640_MASK = 0b00010000,
  /** Enable PAL CRT-like scan-line emulation */
  VIC4_PALEMU_MASK = 0b00100000,
  /** C65GS FAST mode (48MHz) */
  VIC4_VFAST_MASK = 0b01000000,
  /** Alpha compositor enable */
  VIC4_ALPHEN_MASK = 0b10000000,
  /** side border width (MSB) */
  VIC4_SDBDRWD_MSB_MASK = 0b00111111,
  /** Enable raster delay (delays raster counter and interrupts by one line to
   * match output pipeline latency) */
  VIC4_RST_DELEN_MASK = 0b01000000,
  /** Enable VIC-II hot registers. When enabled, touching many VIC-II registers
   * causes the VIC-IV to recalculate display parameters, such as border
   * positions and sizes */
  VIC4_HOTREG_MASK = 0b10000000,
  /** screen RAM precise base address (bits 31 - 24) */
  VIC4_SCRNPTRMB_MASK = 0b00001111,
  /** Number of characters to display per */
  VIC4_CHRCOUNT_MASK = 0b00110000,
  /** source full-colour character data from expansion RAM */
  VIC4_EXGLYPH_MASK = 0b10000000,
  /** sprite pointer address (bits 23 - 16) */
  VIC4_SPRPTRBNK_MASK = 0b01111111,
  /** 16-bit sprite pointer mode (allows sprites to be located on any 64 byte
   * boundary in chip RAM) */
  VIC4_SPR_PTR16_MASK = 0b10000000,
  /** first VIC-II raster line */
  VIC4_RASLINE0_MASK = 0b00111111,
  /** Select more VGA-compatible mode if set, instead of HDMI/HDTV VIC-II
   * cycle-exact frame timing. May help to produce a functional display on older
   * VGA monitors. */
  VIC4_VGAHDTV_MASK = 0b01000000,
  /** NTSC emulation mode (max raster = 262) */
  VIC4_PALNTSC_MASK = 0b10000000,
  /** VIC-IV bitmap/text palette bank (alternate palette) */
  VIC4_ABTPALSEL_MASK = 0b00000011,
  /** sprite palette bank */
  VIC4_SPRPALSEL_MASK = 0b00001100,
  /** bitmap/text palette bank */
  VIC4_BTPALSEL_MASK = 0b00110000,
  /** palette bank mapped at $D100-$D3FF */
  VIC4_MAPEDPAL_MASK = 0b11000000,
  /** Alpha delay for compositor */
  VIC4_ALPHADELAY_MASK = 0b00001111,
  /** physical rasters per VIC-II raster (1 to 16) */
  VIC4_RASTERHEIGHT_MASK = 0b11110000,
  /** Raster compare value MSB */
  VIC4_RASCMP_MSB_MASK = 0b00000111,
  /** Continuously monitor sprite pointer, to allow changing sprite data source
   * while a sprite is being drawn */
  VIC4_SPTR_CONT_MASK = 0b00001000,
  /** Reserved. */
  VIC4_RESV_MASK = 0b00110000,
  /** Enable additional IRQ sources, e.g., raster X position. */
  VIC4_EXTIRQS_MASK = 0b01000000,
  /** Raster compare is in physical rasters if clear, or VIC-II rasters if set
   * */
  VIC4_FNRST_CMP_MASK = 0b10000000,
  /** Set which 128KB bank bitplanes */
  VIC4_BIT_PBANK_MASK = 0b00000111,
  /** @RESV */
  GS_VIC4_RESV_MASK = 0b00001000,
  /** hsync polarity */
  VIC4_HSYNCP_MASK = 0b00010000,
  /** vsync polarity */
  VIC4_VSYNCP_MASK = 0b00100000,
  /** VIC-IV debug pixel select red(01), green(10) or blue(11) channel visible
   * in $D07D */
  VIC4_DEBUGC_MASK = 0b11000000
};

#ifdef __cplusplus
} // extern block
#endif
#endif // _VIC4_H
