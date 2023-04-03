// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.
//
// Originally from cc65. Modififed from original version.

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

/* NES controller masks for joy_read() */

#define JOY_BTN_1_MASK          0x80
#define JOY_BTN_2_MASK          0x40
#define JOY_BTN_3_MASK          0x20
#define JOY_BTN_4_MASK          0x10
#define JOY_UP_MASK             0x08
#define JOY_DOWN_MASK           0x04
#define JOY_LEFT_MASK           0x02
#define JOY_RIGHT_MASK          0x01

#define JOY_BTN_A_MASK          JOY_BTN_1_MASK
#define JOY_BTN_B_MASK          JOY_BTN_2_MASK
#define JOY_SELECT_MASK         JOY_BTN_3_MASK
#define JOY_START_MASK          JOY_BTN_4_MASK

#define JOY_BTN_A(v)            ((v) & JOY_BTN_A_MASK)
#define JOY_BTN_B(v)            ((v) & JOY_BTN_B_MASK)
#define JOY_SELECT(v)           ((v) & JOY_SELECT_MASK)
#define JOY_START(v)            ((v) & JOY_START_MASK)

#define JOY_FIRE2_MASK          JOY_BTN_2_MASK
#define JOY_FIRE2(v)            ((v) & JOY_FIRE2_MASK)

/* Additional mouse button mask */
#define MOUSE_BTN_MIDDLE        0x02

/* get_tv() return codes
** set_tv() argument codes
*/
enum {
    TV_NONE                     = 0x00,
    TV_VGA,
    TV_NTSC_COLOR,
    TV_RGB,
    TV_NONE2,
    TV_VGA2,
    TV_NTSC_MONO,
    TV_RGB2
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
enum {
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
void cx16_k_clock_get_date_time(cx16_date_time_t *datetime_ptr);
void cx16_k_clock_set_date_time(unsigned char year, unsigned char mon, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec, unsigned char jif);
unsigned char cx16_k_console_get_char(void);
void cx16_k_console_init(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
void cx16_k_console_put_char(unsigned char c, unsigned char wrapwordflag);
void cx16_k_console_put_image(void *imageaddr, unsigned int width, unsigned int height);
void cx16_k_console_set_paging_message(void *msgaddr);
void cx16_k_enter_basic(unsigned char coldstart) __attribute__((noreturn));
unsigned long cx16_k_entropy_get(void); // returns 24-bit value
void cx16_k_fb_cursor_next_line(unsigned int x);
void cx16_k_fb_cursor_position(unsigned int x, unsigned int y);
void cx16_k_fb_fill_pixels(unsigned int count, unsigned int step, unsigned char color);
void cx16_k_fb_filter_pixels(void *filterfunc, unsigned int count);
void cx16_k_fb_get_info(cx16_fb_info_t *info_ptr);
unsigned char fb_get_pixel(void);
void fb_get_pixels(void *pixeladdr, unsigned int count);
void cx16_k_fb_init(void);
void fb_move_pixels(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int count);
void fb_set_8_pixels(unsigned char pattern, unsigned char color);
void fb_set_8_pixels_opaque(unsigned char pattern, unsigned char mask, unsigned char color1, unsigned char color2);
void fb_set_palette(void *paladdr, unsigned char index, unsigned char count);
void cx16_k_graph_clear(void);
void cx16_k_graph_draw_image(unsigned int x, unsigned int y, void *imageaddr, unsigned int width, unsigned int height);
void cx16_k_graph_draw_line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void cx16_k_graph_draw_oval(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int corner_radius, unsigned char fillflag);
void cx16_k_graph_draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int corner_radius, unsigned char fillflag);
long cx16_k_graph_get_char_size(unsigned char c, unsigned char style); // if printable returns info (0x00bbwwhh), else negative style byte (0xFF0000ss)
void cx16_k_graph_init(graph_fb_functions_t *fb_funcs_ptr);
void cx16_k_graph_move_rect(unsigned int sx, unsigned int sy, unsigned int tx, unsigned int ty, unsigned int width, unsigned int height);
void fb_graph_put_char(graph_pos_t *pos_ptr, unsigned char c);
void fb_graph_set_colors(unsigned char stroke, unsigned char fill, unsigned char background);
void cx16_k_graph_set_font(void *fontaddr);
void cx16_k_graph_set_window(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
int cx16_k_i2c_read_byte(unsigned char device, unsigned char offset); // returns negative on error
int cx16_k_i2c_write_byte(unsigned char device, unsigned char offset, unsigned char byte); // return negative on error
long cx16_k_joystick_get(unsigned char sticknum); // returns $YYYYXXAA (see docs, result negative if joystick not present)
void cx16_k_joystick_scan(void);
unsigned char cx16_k_kbdbuf_get_modifiers(void);
int cx16_k_kbdbuf_peek(void); // returns negative if empty
unsigned char cx16_k_kbdbuf_peek_len(void);
void cx16_k_kbdbuf_put(unsigned char c);
const char* cx16_k_keymap_get_id(void);
unsigned char cx16_k_keymap_set(const char* identifier);	// returns 0 on success
long cx16_k_macptr(unsigned char count, unsigned char noadvance, void *destaddr); // return negative if not supported
void cx16_k_memory_copy(void *source, void *target, unsigned int num_bytes);
void * cx16_k_memory_crc(void *dataaddr, unsigned int num_bytes);
void cx16_k_memory_decompress(void *inaddr, void *outaddr);
void cx16_k_memory_fill(void *addr, unsigned int num_bytes, unsigned char value);
void cx16_k_monitor(void) __attribute__((noreturn));
void cx16_k_mouse_config(unsigned char showmouse, unsigned char xsize8, unsigned char ysize8);
unsigned char cx16_k_mouse_get(mouse_pos_t *mouse_pos_ptr);	// returns mouse button byte
void cx16_k_mouse_scan(void);
unsigned char cx16_k_savehl(void *startaddr, void *endaddr_plusone); // returns 0 on success
unsigned char cx16_k_screen_mode_get(screen_mode_info_t *info_ptr); // returns 0 on success
unsigned char cx16_k_screen_mode_set(unsigned char mode); // returns 0 on success
void cx16_k_screen_set_charset(unsigned char charset_type, void *charsetaddr);
unsigned char cx16_k_sprite_set_image(unsigned char num, unsigned char w, unsigned char h, unsigned char maskflag, void *imageaddr, void *maskaddr, unsigned char bpp); // returns 0 on success
unsigned char cx16_k_sprite_set_position(unsigned char sprnum, unsigned int xpos, unsigned int ypos); // returns 0 on success

/* End of cX16.h */
#endif
