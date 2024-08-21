// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65. Modified from original version.

// clang-format off

/*****************************************************************************/
/*                                                                           */
/*                                  cx16.h                                   */
/*                                                                           */
/*                      CX16 system-specific definitions                     */
/*                             For prerelease 39                             */
/*                                                                           */
/*                                                                           */
/* This software is provided "as-is", without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated, but is not required.                                      */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/

#ifndef _CX16_H
#define _CX16_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Check for errors */
#ifndef __CX16__
#  error This module may be used only when compiling for the CX16!
#endif



/*****************************************************************************/
/*                                   Data                                    */
/*****************************************************************************/



/* Additional output character codes */
#define CH_COLOR_SWAP           0x01
#define CH_UNDERLINE            0x04
#define CH_WHITE                0x05
#define CH_BOLD                 0x06
#define CH_BACKSPACE            0x08
#define CH_ITALIC               0x0B
#define CH_OUTLINE              0x0C
#define CH_FONT_ISO             0x0F
#define CH_RED                  0x1C
#define CH_GREEN                0x1E
#define CH_BLUE                 0x1F
#define CH_ORANGE               0x81
#define CH_FONT_PET             0x8F
#define CH_BLACK                0x90
#define CH_ATTR_CLEAR           0x92
#define CH_BROWN                0x95
#define CH_PINK                 0x96
#define CH_LIGHTRED             CH_PINK
#define CH_GRAY1                0x97
#define CH_GRAY2                0x98
#define CH_LIGHTGREEN           0x99
#define CH_LIGHTBLUE            0x9A
#define CH_GRAY3                0x9B
#define CH_PURPLE               0x9C
#define CH_YELLOW               0x9E
#define CH_CYAN                 0x9F
#define CH_SHIFT_SPACE          0xA0

/* Additional key defines */
#define CH_SHIFT_TAB            0x18
#define CH_HELP                 0x84
#define CH_F1                   0x85
#define CH_F2                   0x89
#define CH_F3                   0x86
#define CH_F4                   0x8A
#define CH_F5                   0x87
#define CH_F6                   0x8B
#define CH_F7                   0x88
#define CH_F8                   0x8C
#define CH_F9                   0x10
#define CH_F10                  0x15
#define CH_F11                  0x16
#define CH_F12                  0x17

/* Color defines */
#define COLOR_BLACK             0x00
#define COLOR_WHITE             0x01
#define COLOR_RED               0x02
#define COLOR_CYAN              0x03
#define COLOR_PURPLE            0x04
#define COLOR_GREEN             0x05
#define COLOR_BLUE              0x06
#define COLOR_YELLOW            0x07
#define COLOR_ORANGE            0x08
#define COLOR_BROWN             0x09
#define COLOR_PINK              0x0A
#define COLOR_LIGHTRED          COLOR_PINK
#define COLOR_GRAY1             0x0B
#define COLOR_GRAY2             0x0C
#define COLOR_LIGHTGREEN        0x0D
#define COLOR_LIGHTBLUE         0x0E
#define COLOR_GRAY3             0x0F

/// NES controller masks for JoyState
enum : unsigned char {
  // Masks for JoyState::data0
  JOY_BTN_B_MASK = 1 << 7,
  JOY_BTN_Y_MASK = 1 << 6,
  JOY_SELECT_MASK = 1 << 5,
  JOY_START_MASK = 1 << 4,
  JOY_UP_MASK = 1 << 3,
  JOY_DOWN_MASK = 1 << 2,
  JOY_LEFT_MASK = 1 << 1,
  JOY_RIGHT_MASK = 1 << 0,
  // Masks for JoyState::data1
  JOY_BTN_A_MASK = 1 << 7,
  JOY_BTN_X_MASK = 1 << 6,
  JOY_FIRE_LEFT_MASK = 1 << 5,
  JOY_FIRE_RIGHT_MASK = 1 << 4
};

/// Joystick selection
#define JOY_KEYBOARD 0
#define JOY_SNES_PORT1 1
#define JOY_SNES_PORT2 2
#define JOY_SNES_PORT3 3
#define JOY_SNES_PORT4 4

/// Status of SNES joystick populated by cx16_k_joystick_get();
struct JoyState {
  union {
    struct {
      unsigned char data0; //!< Bits: B Y Select Start Up Down Left Right
      unsigned char data1; //!< Bits: A X FireL  FireR 1  1    1    1
    };
    unsigned short data; //!< data0 and data1 combined
  };
  bool detached; //!< True if joystick is disconnected

#ifdef __cplusplus
  bool button_a() const { return !(data1 & JOY_BTN_A_MASK); }
  bool button_b() const { return !(data0 & JOY_BTN_B_MASK); }
  bool button_x() const { return !(data1 & JOY_BTN_X_MASK); }
  bool button_y() const { return !(data0 & JOY_BTN_Y_MASK); }
  bool fire_left() const { return !(data1 & JOY_FIRE_LEFT_MASK); }
  bool fire_right() const { return !(data1 & JOY_FIRE_RIGHT_MASK); }
  bool select() const { return !(data0 & JOY_SELECT_MASK); }
  bool start() const { return !(data0 & JOY_START_MASK); }
  bool north() const { return !(data0 & JOY_UP_MASK); }
  bool south() const { return !(data0 & JOY_DOWN_MASK); }
  bool east() const { return !(data0 & JOY_RIGHT_MASK); }
  bool west() const { return !(data0 & JOY_LEFT_MASK); }
  bool north_east() const { return !(data0 & (JOY_UP_MASK | JOY_RIGHT_MASK)); }
  bool north_west() const { return !(data0 & (JOY_UP_MASK | JOY_LEFT_MASK)); }
  bool south_east() const {
    return !(data0 & (JOY_DOWN_MASK | JOY_RIGHT_MASK));
  }
  bool south_west() const { return !(data0 & (JOY_DOWN_MASK | JOY_LEFT_MASK)); }
#endif
};

/* Additional mouse button mask */
#define MOUSE_BTN_MIDDLE        0x02

/* get_tv() return codes
** set_tv() argument codes
** NOTE: llvm-mos-sdk added newer 240P modes
*/
enum {
    TV_NONE                     = 0x00,
    TV_VGA,
    TV_NTSC_COLOR,
    TV_RGB,
    TV_NONE2,
    TV_VGA2,
    TV_NTSC_MONO,
    TV_RGB2,
    TV_NONE_240P,
    TV_VGA_240P,
    TV_NTSC_COLOR_240P,
    TV_RGB_240P,
    TV_NONE2_240P,
    TV_VGA2_240P,
    TV_NTSC_MONO_240P,
    TV_RGB2_240P
};

/* Video modes for videomode() */
#define VIDEOMODE_80x60         0x00
#define VIDEOMODE_80x30         0x01
#define VIDEOMODE_40x60         0x02
#define VIDEOMODE_40x30         0x03
#define VIDEOMODE_40x15         0x04
#define VIDEOMODE_20x30         0x05
#define VIDEOMODE_20x15         0x06
#define VIDEOMODE_80COL         VIDEOMODE_80x60
#define VIDEOMODE_40COL         VIDEOMODE_40x30
#define VIDEOMODE_320x240       0x80
#define VIDEOMODE_SWAP          (-1)

/* VERA's address increment/decrement numbers */
enum : unsigned char {
    VERA_DEC_0                  = ((0 << 1) | 1) << 3,
    VERA_DEC_1                  = ((1 << 1) | 1) << 3,
    VERA_DEC_2                  = ((2 << 1) | 1) << 3,
    VERA_DEC_4                  = ((3 << 1) | 1) << 3,
    VERA_DEC_8                  = ((4 << 1) | 1) << 3,
    VERA_DEC_16                 = ((5 << 1) | 1) << 3,
    VERA_DEC_32                 = ((6 << 1) | 1) << 3,
    VERA_DEC_64                 = ((7 << 1) | 1) << 3,
    VERA_DEC_128                = ((8 << 1) | 1) << 3,
    VERA_DEC_256                = ((9 << 1) | 1) << 3,
    VERA_DEC_512                = ((10 << 1) | 1) << 3,
    VERA_DEC_40                 = ((11 << 1) | 1) << 3,
    VERA_DEC_80                 = ((12 << 1) | 1) << 3,
    VERA_DEC_160                = ((13 << 1) | 1) << 3,
    VERA_DEC_320                = ((14 << 1) | 1) << 3,
    VERA_DEC_640                = ((15 << 1) | 1) << 3,
    VERA_INC_0                  = ((0 << 1) | 0) << 3,
    VERA_INC_1                  = ((1 << 1) | 0) << 3,
    VERA_INC_2                  = ((2 << 1) | 0) << 3,
    VERA_INC_4                  = ((3 << 1) | 0) << 3,
    VERA_INC_8                  = ((4 << 1) | 0) << 3,
    VERA_INC_16                 = ((5 << 1) | 0) << 3,
    VERA_INC_32                 = ((6 << 1) | 0) << 3,
    VERA_INC_64                 = ((7 << 1) | 0) << 3,
    VERA_INC_128                = ((8 << 1) | 0) << 3,
    VERA_INC_256                = ((9 << 1) | 0) << 3,
    VERA_INC_512                = ((10 << 1) | 0) << 3,
    VERA_INC_40                 = ((11 << 1) | 0) << 3,
    VERA_INC_80                 = ((12 << 1) | 0) << 3,
    VERA_INC_160                = ((13 << 1) | 0) << 3,
    VERA_INC_320                = ((14 << 1) | 0) << 3,
    VERA_INC_640                = ((15 << 1) | 0) << 3
};

/* VERA's interrupt flags */
#define VERA_IRQ_VSYNC          0b00000001
#define VERA_IRQ_RASTER         0b00000010
#define VERA_IRQ_SPR_COLL       0b00000100
#define VERA_IRQ_AUDIO_LOW      0b00001000

/* Define hardware. */

#define RAM_BANK        (*(volatile unsigned char *)0x00)
#define ROM_BANK        (*(volatile unsigned char *)0x01)

#include <_6522.h>
#define VIA1    (*(volatile struct __6522 *)0x9F00)
#define VIA2    (*(volatile struct __6522 *)0x9F10)

/* A structure with the Video Enhanced Retro Adapter's external registers */
struct __vera {
    unsigned short      address;        /* Address for data ports */
    unsigned char       address_hi;
    unsigned char       data0;          /* Data port 0 */
    unsigned char       data1;          /* Data port 1 */
    unsigned char       control;        /* Control register */
    unsigned char       irq_enable;     /* Interrupt enable bits */
    unsigned char       irq_flags;      /* Interrupt flags */
    unsigned char       irq_raster;     /* Line where IRQ will occur */
    union {
        struct {                        /* Visible when DCSEL flag = 0 */
            unsigned char video;        /* Flags to enable video layers */
            unsigned char hscale;       /* Horizontal scale factor */
            unsigned char vscale;       /* Vertical scale factor */
            unsigned char border;       /* Border color (NTSC mode) */
        };
        struct {                        /* Visible when DCSEL flag = 1 */
            unsigned char hstart;       /* Horizontal start position */
            unsigned char hstop;        /* Horizontal stop position */
            unsigned char vstart;       /* Vertical start position */
            unsigned char vstop;        /* Vertical stop position */
        };
        struct {                        /* Visible when DCSEL flag = 2 */
            unsigned char fxctrl;
            unsigned char fxtilebase;
            unsigned char fxmapbase;
            unsigned char fxmult;
        };
        struct {                        /* Visible when DCSEL flag = 3 */
            unsigned char fxxincrl;
            unsigned char fxxincrh;
            unsigned char fxyincrl;
            unsigned char fxyincrh;
        };
        struct {                        /* Visible when DCSEL flag = 4 */
            unsigned char fxxposl;
            unsigned char fxxposh;
            unsigned char fxyposl;
            unsigned char fxyposh;
        };
        struct {                        /* Visible when DCSEL flag = 5 */
            unsigned char fxxposs;
            unsigned char fxyposs;
            unsigned char fxpolyfilll;
            unsigned char fxpolyfillh;
        };
        struct {                        /* Visible when DCSEL flag = 6 */
            unsigned char fxcachel;
            unsigned char fxcachem;
            unsigned char fxcacheh;
            unsigned char fxcacheu;
        };
        struct {                        /* Visible when DCSEL flag = 63 */
            unsigned char dcver0;
            unsigned char dcver1;
            unsigned char dcver2;
            unsigned char dcver3;
        };
    } display;
    struct {
        unsigned char   config;         /* Layer map geometry */
        unsigned char   mapbase;        /* Map data address */
        unsigned char   tilebase;       /* Tile address and geometry */
        unsigned int    hscroll;        /* Smooth scroll horizontal offset */
        unsigned int    vscroll;        /* Smooth scroll vertical offset */
    } layer0;
    struct {
        unsigned char   config;
        unsigned char   mapbase;
        unsigned char   tilebase;
        unsigned int    hscroll;
        unsigned int    vscroll;
    } layer1;
    struct {
        unsigned char   control;        /* PCM format */
        unsigned char   rate;           /* Sample rate */
        unsigned char   data;           /* PCM output queue */
    } audio;                            /* Pulse-Code Modulation registers */
    struct {
        unsigned char   data;
        unsigned char   control;
    } spi;                              /* SD card interface */
};
#define VERA    (*(volatile struct __vera *)0x9F20)

/* Audio chip */
struct __ym2151 {
    union {
        unsigned char   reg;            /* Register number for data */
        unsigned char   status;         /* Busy flag */
    };
    unsigned char       data;
};
#define YM2151  (*(volatile struct __ym2151 *)0x9F40)

/* A structure with the x16emu's settings registers */
struct __emul {
    unsigned char       debug;          /* Boolean: debugging enabled */
    unsigned char       vera_action;    /* Boolean: displaying VERA activity */
    unsigned char       keyboard;       /* Boolean: displaying typed keys */
    unsigned char       echo;           /* How to send Kernal output to host */
    unsigned char       save_on_exit;   /* Boolean: save machine state on exit */
    unsigned char       gif_method;     /* How GIF movie is being recorded */
    unsigned char const unused1[2];
    unsigned long const cycle_count;    /* Running total of CPU cycles (8 MHz.) */
    unsigned char const unused2[1];
    unsigned char const keymap;         /* Keyboard layout number */
             char const detect[2];      /* "16" if running on x16emu */
};
#define EMULATOR        (*(volatile struct __emul *)0x9FB0)

/* An array window into the half Mebibyte or two Mebibytes of banked RAM */
#define BANK_RAM        ((volatile unsigned char *)0xA000)

/*****************************************************************************/
/*                          CX16 kernal functions                            */
/*****************************************************************************/

/* Kernel function structure type definitions */
typedef struct
{
    unsigned char year, mon, day, hour, min, sec, jif;
} cx16_date_time_t; /* cx16_k_clock_get_date_time() */

typedef struct
{
    unsigned int width, height;
    unsigned char depth;
} cx16_fb_info_t; /* cx16_k_fb_get_info_depth() */

typedef struct
{
    void *fb_init;
    void *fb_get_info;
    void *fb_set_palette;
    void *fb_cursor_position;
    void *fb_cursor_next_line;
    void *fb_get_pixel;
    void *fb_get_pixels;
    void *fb_set_pixel;
    void *fb_set_pixels;
    void *fb_set_8_pixels;
    void *fb_set_8_pixels_opaque;
    void *fb_fill_pixels;
    void *fb_filter_pixels;
    void *fb_move_pixels;
} graph_fb_functions_t; /* cx16_k_graph_init() */

typedef struct
{
    int x, y;
} graph_pos_t;  /* fb_graph_put_char() */

typedef struct
{
    int x, y;
} mouse_pos_t; /* cx16_k_mouse_get() */

typedef struct
{
    unsigned char mode, columns, rows;
} screen_mode_info_t;   /* cx16_k_screen_mode_get() */

/* Kernal-level functions */
unsigned char cx16_k_bsave(void *startaddr, void *endaddr_plusone) __attribute__((leaf)); // returns 0 on success
void cx16_k_clock_get_date_time(cx16_date_time_t *datetime_ptr) __attribute__((leaf));
void cx16_k_clock_set_date_time(unsigned char year, unsigned char mon, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec, unsigned char jif) __attribute__((leaf));
unsigned char cx16_k_console_get_char(void) __attribute__((leaf));
void cx16_k_console_init(unsigned int x, unsigned int y, unsigned int width, unsigned int height) __attribute__((leaf));
void cx16_k_console_put_char(unsigned char c, unsigned char wrapwordflag) __attribute__((leaf));
void cx16_k_console_put_image(void *imageaddr, unsigned int width, unsigned int height) __attribute__((leaf));
void cx16_k_console_set_paging_message(void *msgaddr) __attribute__((leaf));
void cx16_k_enter_basic(unsigned char coldstart) __attribute__((noreturn));
unsigned long cx16_k_entropy_get(void) __attribute__((leaf)); // returns 24-bit value
void cx16_k_fb_cursor_next_line(unsigned int x) __attribute__((leaf));
void cx16_k_fb_cursor_position(unsigned int x, unsigned int y) __attribute__((leaf));
void cx16_k_fb_fill_pixels(unsigned int count, unsigned int step, unsigned char color) __attribute__((leaf));
void cx16_k_fb_filter_pixels(void *filterfunc, unsigned int count) __attribute__((leaf));
void cx16_k_fb_get_info(cx16_fb_info_t *info_ptr) __attribute__((leaf));
unsigned char fb_get_pixel(void) __attribute__((leaf));
void cx16_k_fb_get_pixels(void *pixeladdr, unsigned int count) __attribute__((leaf));
void cx16_k_fb_init(void) __attribute__((leaf));
void cx16_k_fb_move_pixels(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int count) __attribute__((leaf));
void cx16_k_fb_set_8_pixels(unsigned char pattern, unsigned char color) __attribute__((leaf));
void cx16_k_fb_set_8_pixels_opaque(unsigned char pattern, unsigned char mask, unsigned char color1, unsigned char color2) __attribute__((leaf));
void cx16_k_fb_set_palette(void *paladdr, unsigned char index, unsigned char count __attribute__((leaf)));
void cx16_k_graph_clear(void) __attribute__((leaf));
void cx16_k_graph_draw_image(unsigned int x, unsigned int y, void *imageaddr, unsigned int width, unsigned int height) __attribute__((leaf));
void cx16_k_graph_draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) __attribute__((leaf));
void cx16_k_graph_draw_oval(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int corner_radius, unsigned char fillflag) __attribute__((leaf));
void cx16_k_graph_draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int corner_radius, unsigned char fillflag __attribute__((leaf)));
long cx16_k_graph_get_char_size(unsigned char c, unsigned char style) __attribute__((leaf)); // if printable returns info (0x00bbwwhh), else negative style byte (0xFF0000ss)
void cx16_k_graph_init(graph_fb_functions_t *fb_funcs_ptr) __attribute__((leaf));
void cx16_k_graph_move_rect(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int width, unsigned int height) __attribute__((leaf));
void cx16_k_graph_put_char(graph_pos_t *pos_ptr, unsigned char c) __attribute__((leaf));
void cx16_k_graph_set_colors(unsigned char stroke, unsigned char fill, unsigned char background) __attribute__((leaf));
void cx16_k_graph_set_font(void *fontaddr) __attribute__((leaf));
void cx16_k_graph_set_window(unsigned int x, unsigned int y, unsigned int width, unsigned int height) __attribute__((leaf));
int cx16_k_i2c_read_byte(unsigned char device, unsigned char offset) __attribute__((leaf)); // returns negative on error
int cx16_k_i2c_write_byte(unsigned char device, unsigned char offset, unsigned char byte) __attribute__((leaf)); // return negative on error

/**
 * Get joystick state using KERNAL routine `JOYSTICK_GET`.
 *
 * More information: https://github.com/X16Community/x16-docs
 *
 * @param joystick_num Keyboard joystick (0) or SNES controllers (1-4).
 * @returns Struct with current status.
 */
struct JoyState cx16_k_joystick_get(unsigned char joystick_num);

void cx16_k_joystick_scan(void) __attribute__((leaf));
unsigned char cx16_k_kbdbuf_get_modifiers(void) __attribute__((leaf));
int cx16_k_kbdbuf_peek(unsigned char *index_ptr)
    __attribute__((leaf)); // returns negative if empty, if index_ptr non-NULL
                           // set contents to queue length
void cx16_k_kbdbuf_put(unsigned char c) __attribute__((leaf));
const char* cx16_k_keymap_get_id(void) __attribute__((leaf));
unsigned char cx16_k_keymap_set(const char* identifier) __attribute__((leaf));	// returns 0 on success
long cx16_k_macptr(unsigned char count, unsigned char noadvance, void *destaddr) __attribute__((leaf)); // return negative if not supported
void cx16_k_memory_copy(void *source, void *target, unsigned int num_bytes) __attribute__((leaf));
unsigned int cx16_k_memory_crc(void *dataaddr, unsigned int num_bytes) __attribute__((leaf));
void cx16_k_memory_decompress(void *inaddr, void *outaddr) __attribute__((leaf));
void cx16_k_memory_fill(void *addr, unsigned int num_bytes, unsigned char value) __attribute__((leaf));
void cx16_k_monitor(void) __attribute__((noreturn));
void cx16_k_mouse_config(unsigned char showmouse, unsigned char xsize8, unsigned char ysize8) __attribute__((leaf));
unsigned char cx16_k_mouse_get(mouse_pos_t *mouse_pos_ptr) __attribute__((leaf));	// returns mouse button byte
void cx16_k_mouse_scan(void) __attribute__((leaf));
unsigned long cx16_k_rdtim(void) __attribute__((leaf));
unsigned char cx16_k_screen_mode_get(screen_mode_info_t *info_ptr) __attribute__((leaf)); // returns 0 on success
unsigned char cx16_k_screen_mode_set(unsigned char mode) __attribute__((leaf)); // returns 0 on success
void cx16_k_screen_set_charset(unsigned char charset_type, void *charsetaddr) __attribute__((leaf));
unsigned char cx16_k_sprite_set_image(unsigned char num, unsigned char w, unsigned char h, unsigned char maskflag, void *imageaddr, void *maskaddr, unsigned char bpp) __attribute__((leaf)); // returns 0 on success
unsigned char cx16_k_sprite_set_position(unsigned char sprnum, unsigned int xpos, unsigned int ypos) __attribute__((leaf)); // returns 0 on success

/* cc65 compatible cx16 functions */

/* Return the number of 8K RAM banks that the machine has */
/* at 0xA000-0xBFFF using MEMTOP (64=512K up to 256=2MB) */
unsigned short get_numbanks(void) __attribute__((leaf)); // return number of 8K RAM banks at 0xA000-0xBFFF (64=512K up to 256=2MB)

/* Get the ROM build version.
** -1 -- custom build
** Negative -- prerelease build
** Positive -- release build
*/
signed char get_ostype(void) __attribute__((leaf));  // return ROM build version (negative pre-release, -1=custom)

/* Return the video signal type that the machine is using.
** Return a TV_xx constant.
*/
unsigned char get_tv(void) __attribute__((leaf));    // return TV_* enum constant for current video signal type

/* Set the video signal type that the machine will use.
** Call with a TV_xx constant.
** NOTE: Be careful, can overrides user setting for current monitor type (set in config menu)
*/
void set_tv(unsigned char type) __attribute__((leaf));    // set video signal type using TV_* enum constant

/* Display the layers that are "named" by the bit flags in layers.
** A value of 0b01 shows layer 0, a value of 0b10 shows layer 1,
** a value of 0b11 shows both layers.  Return the previous value.
*/
unsigned char vera_layer_enable(unsigned char layers) __attribute__((leaf)); // enable/disable VERA layers 0/1 (bits 0/1), returns previous

/* Enable the sprite engine when mode is non-zero (true);
** disable sprites when mode is zero.  Return the previous mode.
*/
unsigned char vera_sprites_enable(unsigned char enable) __attribute__((leaf)); // enable/disable VERA sprites (0=off, non-zero=on), returns previous

/* Set the video mode, return the old mode.
** Return -1 if Mode isn't valid.
** Call with one of the VIDEOMODE_xx constants.
*/
signed char videomode(signed char mode) __attribute__((leaf));   // set video mode using VIDEOMODE_* enum constant, returns previous or -1 if error

/* Get a byte from a location in VERA's internal address space. */
unsigned char vpeek(unsigned long addr) __attribute__((leaf));    // read byte from VERA VRAM address

/* Put a byte into a location in VERA's internal address space.
** (addr is second instead of first for the sake of code efficiency.)
*/
void vpoke(unsigned char data, unsigned long addr) __attribute__((leaf)); // write byte value to VERA VRAM address

void waitvsync(void);  // wait for the vertical blank interrupt

#ifdef __cplusplus
}
#endif
#endif  // _CX16_H
