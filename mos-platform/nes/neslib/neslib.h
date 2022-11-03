#ifndef _NESLIB_H_
#define _NESLIB_H_

#include <famitone2.h>

#ifdef __cplusplus
extern "C" {
#endif

// NES hardware-dependent functions by Shiru (shiru@mail.ru)
// Feel free to do anything you want with this code, consider it Public Domain

// for nesdoug version 1.2, 1/1/2022
// changes, removed sprid from oam functions, oam_spr 11% faster, meta 5% faster

// Versions history:
//  050517 - pad polling code optimized, button bits order reversed
//  280215 - fixed palette glitch caused by the active DMC DMA glitch
//  030914 - minor fixes in the VRAM update system
//  310814 - added vram_flush_update
//  120414 - removed adr argument from vram_write and vram_read,
//           unrle_vram renamed to vram_unrle, with adr argument removed
//  060414 - many fixes and improvements, including sequential VRAM updates
//  previous versions were created since mid-2011, there were many updates

// set bg and spr palettes, data is 32 bytes array
__attribute__((leaf)) void pal_all(const void *data);

// set bg palette only, data is 16 bytes array
__attribute__((leaf)) void pal_bg(const void *data);

// set spr palette only, data is 16 bytes array
__attribute__((leaf)) void pal_spr(const void *data);

// set a palette entry, index is 0..31
void pal_col(char index, char color);

// reset palette to $0f
__attribute__((leaf)) void pal_clear(void);

// set virtual bright both for sprites and background, 0 is black, 4 is normal,
// 8 is white
void pal_bright(char bright);

// set virtual bright for sprites only
void pal_spr_bright(char bright);

// set virtual bright for sprites background only
void pal_bg_bright(char bright);

// wait actual TV frame, 50hz for PAL, 60hz for NTSC
__attribute__((leaf)) void ppu_wait_nmi(void);

// wait virtual frame, it is always 50hz, frame-to-frame in PAL, frameskip in
// NTSC don't use this one
__attribute__((leaf)) void ppu_wait_frame(void);

// turn off rendering, nmi still enabled when rendering is disabled
void ppu_off(void);

// turn on bg, spr
void ppu_on_all(void);

// turn on bg only
void ppu_on_bg(void);

// turn on spr only
void ppu_on_spr(void);

// set PPU_MASK directly
void ppu_mask(char mask);

// get current video system, 0 for PAL, not 0 for NTSC
char ppu_system(void);

// clear OAM buffer, all the sprites are hidden
//  Note: changed. Now also changes sprid (index to buffer) to zero
__attribute__((leaf)) void oam_clear(void);

// set sprite display mode, 0 for 8x8 sprites, 1 for 8x16 sprites
__attribute__((leaf)) void oam_size(char size);

// set sprite in OAM buffer, chrnum is tile, attr is attribute
//  Note: sprid removed for speed
__attribute__((leaf)) void oam_spr(char x, char y, char chrnum, char attr);

// set metasprite in OAM buffer
// meta sprite is a const char array, it contains four bytes per sprite
// in order x offset, y offset, tile, attribute
// x=128 is end of a meta sprite
//  Note: sprid removed for speed
__attribute__((leaf)) void oam_meta_spr(char x, char y, const void *data);

// hide all remaining sprites from given offset
//  Note: sprid removed for speed
//  Now also changes sprid (index to buffer) to zero
__attribute__((leaf)) void oam_hide_rest(void);

// to manually change the sprid (index to sprite buffer)
// perhaps as part of a sprite shuffling algorithm
// Note: this should be a multiple of 4 (0,4,8,12,etc.)
void oam_set(char index);

// returns the sprid (index to the sprite buffer)
char oam_get(void);

// poll controller and return flags like PAD_LEFT etc, input is pad number (0 or
// 1)
__attribute__((leaf)) char pad_poll(char pad);

// poll controller in trigger mode, a flag is set only on button down, not hold
// if you need to poll the pad in both normal and trigger mode, poll it in the
// trigger mode for first, then use pad_state
char pad_trigger(char pad);

// get previous pad state without polling ports
char pad_state(char pad);

// set scroll, including the top bits
// it is always applied at beginning of a TV frame, not at the function call
__attribute__((leaf)) void scroll(unsigned x, unsigned y);

// set scroll after screen split invoked by the sprite 0 hit
// warning: all CPU time between the function call and the actual split point
// will be wasted! warning: the program loop has to fit into the frame time,
// ppu_wait_frame should not be used
//          otherwise empty frames without split will be inserted, resulting in
//          jumpy screen
// warning: only X scroll could be changed in this version
__attribute__((leaf)) void split(unsigned x); // removed y, not used %%

// select current chr bank for sprites, 0..1
__attribute__((leaf)) void bank_spr(char n);

// select current chr bank for background, 0..1
__attribute__((leaf)) void bank_bg(char n);

// get random number 0..255
__attribute__((leaf)) char rand8(void);

// get random number 0..65535
__attribute__((leaf)) unsigned rand16(void);

// set random seed
__attribute__((leaf)) void set_rand(unsigned seed);

// when display is enabled, vram access could only be done with this vram update
// system the function sets a pointer to the update buffer that contains data
// and addresses in a special format. It allows to write non-sequential bytes,
// as well as horizontal or vertical nametable sequences. buffer pointer could
// be changed during rendering, but it only takes effect on a new frame number
// of transferred bytes is limited by vblank time to disable updates, call this
// function with NULL pointer
//
// the update data format:
//  MSB, LSB, byte for a non-sequential write
//  MSB|NT_UPD_HORZ, LSB, LEN, [bytes] for a horizontal sequence
//  MSB|NT_UPD_VERT, LSB, LEN, [bytes] for a vertical sequence
//  NT_UPD_EOF to mark end of the buffer
//
// length of this data should be under 256 bytes
void set_vram_update(const void *buf);

// all following vram functions only work when display is disabled

// do a series of VRAM writes, the same format as for set_vram_update, but
// writes done right away
__attribute__((leaf)) void flush_vram_update(const void *buf);

// set vram pointer to write operations if you need to write some data to vram
void vram_adr(unsigned adr);

// put a byte at current vram address, works only when rendering is turned off
void vram_put(char n);

// fill a block with a byte at current vram address, works only when rendering
// is turned off
__attribute__((leaf)) void vram_fill(char n, unsigned len);

// set vram autoincrement, 0 for +1 and not 0 for +32
__attribute__((leaf)) void vram_inc(char n);

// read a block from current address of vram, works only when rendering is
// turned off
__attribute__((leaf)) void vram_read(void *dst, unsigned size);

// write a block to current address of vram, works only when rendering is turned
// off
__attribute__((leaf)) void vram_write(const void *src, unsigned size);

// unpack RLE data to current address of vram, mostly used for nametables
__attribute__((leaf)) void vram_unrle(const void *data);

// delay for N frames
void delay(char frames);

#define PAD_A 0x80
#define PAD_B 0x40
#define PAD_SELECT 0x20
#define PAD_START 0x10
#define PAD_UP 0x08
#define PAD_DOWN 0x04
#define PAD_LEFT 0x02
#define PAD_RIGHT 0x01

#define OAM_FLIP_V 0x80
#define OAM_FLIP_H 0x40
#define OAM_BEHIND 0x20

#define MAX(x1, x2) ((x1) < (x2) ? (x2) : (x1))
#define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))

#define MASK_SPR 0x10
#define MASK_BG 0x08
#define MASK_EDGE_SPR 0x04
#define MASK_EDGE_BG 0x02

#define NAMETABLE_A 0x2000
#define NAMETABLE_B 0x2400
#define NAMETABLE_C 0x2800
#define NAMETABLE_D 0x2c00

#define NULL 0
#define TRUE 1
#define FALSE 0

#define NT_UPD_HORZ 0x40
#define NT_UPD_VERT 0x80
#define NT_UPD_EOF 0xff

// macro to calculate nametable address from X,Y in compile time
#define NTADR_A(x, y) (NAMETABLE_A | (((y) << 5) | (x)))

// macro to calculate nametable address from X,Y in compile time
#define NTADR_B(x, y) (NAMETABLE_B | (((y) << 5) | (x)))

// macro to calculate nametable address from X,Y in compile time
#define NTADR_C(x, y) (NAMETABLE_C | (((y) << 5) | (x)))

// macro to calculate nametable address from X,Y in compile time
#define NTADR_D(x, y) (NAMETABLE_D | (((y) << 5) | (x)))

// macro to get MSB
#define MSB(x) (((x) >> 8))

// macro to get LSB
#define LSB(x) (((x)&0xff))

#ifdef __cplusplus
}
#endif

#endif // _NESLIB_H_
