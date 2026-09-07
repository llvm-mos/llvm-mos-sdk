// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Portions originally from cc65.

#ifndef _VIDEO_H
#define _VIDEO_H

#ifdef __cplusplus
extern "C" {
#endif

// Direction constants for use with lynx_video_settextstyle
#define lynx_video_TEXT_HORIZONTAL     0
#define lynx_video_TEXT_VERTICAL       1

// Initialize the already loaded graphics driver.
void lynx_video_init();

// enable or disable hardware collision detection buffer
void lynx_video_setcollisiondetection(unsigned char enabled);

// swap draw and display buffers
void lynx_video_updatedisplay();

// is drawing complete?
unsigned char lynx_video_busy();

// set LCD refresh rate
void lynx_video_setframerate(unsigned char rate);

// set background color
void lynx_video_setbgcolor(unsigned char color);

// flip screen upside down
void lynx_video_flip();

// draw chained sprites
void lynx_video_sprite(void* sprite);

// Clear the drawpage.
void lynx_video_clear();

// Set the visible page
void lynx_video_setviewpage(unsigned char page);

// Set the drawable page
void lynx_video_setdrawpage(unsigned char page);

// Set the current drawing color (palette index).
void lynx_video_setcolor(unsigned char color_index);

// Return the current drawing color (palette index).
unsigned char lynx_video_getcolor();

// Set the palette. palette is a pointer to 32 entries representing 16 colors
// The first 16 bytes are the green values, the second 16 byts are the red/blue values
void lynx_video_setpalette(const unsigned char* palette);

// Return the current palette, a pointer to 32 entries representing 16 colors
// The first 16 bytes are the green values, the second 16 byts are the red/blue values
const unsigned char* lynx_video_getpalette();

// Return the default palette.
const unsigned char* lynx_video_getdefpalette();

// Get the color value of a pixel.
unsigned char lynx_video_getpixel(unsigned char x, unsigned char y);

// Plot a pixel in the current drawing color.
void lynx_video_setpixel(unsigned char x, unsigned char y);

// Set text scale
void lynx_video_settextstyle(unsigned char width, unsigned char height);

// Output text at the given position.
void lynx_video_outtextxy(unsigned char x, unsigned char y, const char* s);

#ifdef __cplusplus
}
#endif

#endif
