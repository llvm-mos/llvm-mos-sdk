// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

//
// Fixed-point Mandelbrot set with generated charset and color
//
// Uses 8.8 fixed-point arithmetic to compute the classic escape-time
// fractal. Generates a custom charset with increasing pixel density
// and maps iteration counts to MEGA65 palette colors.
// Renders to the 80x25 default screen.

#include <cstdint>
#include <mega65.h>

// 8.8 fixed-point: high byte = integer, low byte = fraction
using fix16 = int16_t;

static constexpr fix16 FP_ONE = 256; // 1.0
static constexpr uint8_t MAX_ITER = 16;

static constexpr uint8_t COLS = 80;
static constexpr uint8_t ROWS = 25;

// View window: real [-2.0, 0.6], imag [-1.2, 1.2]
static constexpr fix16 RE_MIN = -2 * FP_ONE;           // -2.0
static constexpr fix16 RE_MAX = (fix16)(0.6 * FP_ONE); //  0.6
static constexpr fix16 IM_MIN = (fix16)(-1.2 * FP_ONE);
static constexpr fix16 IM_MAX = (fix16)(1.2 * FP_ONE);

// Step sizes (pre-computed to avoid division at runtime)
static constexpr fix16 RE_STEP = (RE_MAX - RE_MIN) / COLS;
static constexpr fix16 IM_STEP = (IM_MAX - IM_MIN) / ROWS;

static constexpr uint16_t CHARSET_ADDR = 0x3000;
// 4x4 Bayer ordered-dither matrix, tiled to 8x8.
// Values 0-15 give 17 threshold levels (0 = no pixels, 16 = all lit).
// Produces clean, structured fill patterns instead of random noise.
// clang-format off
static constexpr uint8_t bayer8x8[8][8] = {
    { 0, 8, 2,10, 0, 8, 2,10},
    {12, 4,14, 6,12, 4,14, 6},
    { 3,11, 1, 9, 3,11, 1, 9},
    {15, 7,13, 5,15, 7,13, 5},
    { 0, 8, 2,10, 0, 8, 2,10},
    {12, 4,14, 6,12, 4,14, 6},
    { 3,11, 1, 9, 3,11, 1, 9},
    {15, 7,13, 5,15, 7,13, 5},
};
// clang-format on

// Generate 17 characters (0-16) with increasing pixel density.
// Character 0 = empty, character 16 = solid block.
// Uses ordered dithering: pixel lights up when char index > Bayer threshold,
// producing smooth gradient transitions between density levels.
static void make_charset() {
  auto *charset = reinterpret_cast<volatile uint8_t *>(CHARSET_ADDR);
  for (uint8_t ch = 0; ch <= MAX_ITER; ++ch) {
    for (uint8_t row = 0; row < 8; ++row) {
      uint8_t pattern = 0;
      for (uint8_t bit = 0; bit < 8; ++bit) {
        if (ch > bayer8x8[row][bit])
          pattern |= (0x80 >> bit);
      }
      *charset++ = pattern;
    }
  }
}

// 8.8 fixed-point multiply: (a * b) >> 8
static inline fix16 fp_mul(fix16 a, fix16 b) {
  return static_cast<fix16>((static_cast<int32_t>(a) * b) >> 8);
}

// Compute Mandelbrot iteration count for point (cr, ci)
static uint8_t mandelbrot(fix16 cr, fix16 ci) {
  constexpr fix16 FP_FOUR = 4 * FP_ONE; // escape radius squared
  fix16 zr = 0, zi = 0;
  for (uint8_t i = 0; i < MAX_ITER; ++i) {
    fix16 zr2 = fp_mul(zr, zr);
    fix16 zi2 = fp_mul(zi, zi);
    if (zr2 + zi2 > FP_FOUR)
      return i;
    zi = fp_mul(zr, zi);
    zi += zi; // 2 * zr * zi
    zi += ci;
    zr = zr2 - zi2 + cr;
  }
  return MAX_ITER;
}

static void setup_vic() {
  // KERNAL uses this zero-page flag to control cursor blinking
  auto *const CURSOR_BLINK = reinterpret_cast<volatile uint8_t *>(0xCC);
  *CURSOR_BLINK = 1;
  asm volatile("sei");

  // Enable MEGA65 fast mode (3.5 MHz) for quicker rendering
  VICIV.ctrlb |= VIC3_FAST_MASK;
  // Extend color RAM window to 2KB ($D800-$DFFF) for 80-column mode.
  // Without this, only $D800-$DBFF (1KB) is visible — not enough
  // for 80x25=2000 bytes. Hides CIA registers while set.
  VICIV.ctrla |= VIC3_CRAM2K_MASK;

  make_charset();
  VICIV.charptr = CHARSET_ADDR;
}

static void render_fractal() {
  // Color palette using standard C64 16 colors (0x00-0x0F).
  // VIC-III attribute mode repurposes bit 4 as blink, so extended
  // palette colors (>=0x10) cannot be used in color RAM directly.
  static constexpr uint8_t colors[] = {
      COLOR_BLUE,       // 0  - escaped immediately
      COLOR_BLUE,       // 1
      COLOR_LIGHTBLUE,  // 2
      COLOR_LIGHTBLUE,  // 3
      COLOR_CYAN,       // 4
      COLOR_CYAN,       // 5
      COLOR_LIGHTGREEN, // 6
      COLOR_GREEN,      // 7
      COLOR_YELLOW,     // 8
      COLOR_YELLOW,     // 9
      COLOR_ORANGE,     // 10
      COLOR_ORANGE,     // 11
      COLOR_RED,        // 12
      COLOR_LIGHTRED,   // 13
      COLOR_BROWN,      // 14
      COLOR_WHITE,      // 15
      COLOR_BLACK,      // 16 - set member
  };
  constexpr uint16_t COLOR_RAM_ADDR = 0xD800;
  auto *screen = reinterpret_cast<volatile uint8_t *>(&DEFAULT_SCREEN);
  auto *color = reinterpret_cast<volatile uint8_t *>(COLOR_RAM_ADDR);

  fix16 ci = IM_MIN;
  for (uint8_t row = 0; row < ROWS; ++row) {
    fix16 cr = RE_MIN;
    for (uint8_t col = 0; col < COLS; ++col) {
      uint8_t iter = mandelbrot(cr, ci);
      *screen++ = iter;
      *color++ = colors[iter];
      cr += RE_STEP;
    }
    ci += IM_STEP;
  }
}

int main() {
  setup_vic();
  render_fractal();

  while (true)
    ;
}
