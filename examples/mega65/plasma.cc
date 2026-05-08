// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

//
// Character-mode plasma effect for MEGA65 (80-column)
//
// MEGA65 features used:
//   - VIC-IV 80-column mode with custom charset
//   - Palette RAM ($D100): 16-color rotating gradient
//   - Enhanced DMA: copies color buffer to $0FF80000 color RAM
//   - 3.5 MHz C65 speed mode
//
// Inspired by cc65/samples/cbm
//   - 2001 by groepaz
//   - Cleanup and porting by Ullrich von Bassewitz
//   - 2023 Mega65/LLVM-MOS C++ adaptation by Mikael Lund aka Wombat
//   - 2026 Colorized by Claude AI Opus 4.6 and Mikael Lund

#include <array>
#include <cstdint>
#include <dma.hpp>
#include <mega65.h>

using namespace mega65::dma;

// Cyclic sine lookup table
static constexpr uint8_t sine_table[UINT8_MAX + 1] = {
    0x80, 0x7d, 0x7a, 0x77, 0x74, 0x70, 0x6d, 0x6a, 0x67, 0x64, 0x61, 0x5e,
    0x5b, 0x58, 0x55, 0x52, 0x4f, 0x4d, 0x4a, 0x47, 0x44, 0x41, 0x3f, 0x3c,
    0x39, 0x37, 0x34, 0x32, 0x2f, 0x2d, 0x2b, 0x28, 0x26, 0x24, 0x22, 0x20,
    0x1e, 0x1c, 0x1a, 0x18, 0x16, 0x15, 0x13, 0x11, 0x10, 0x0f, 0x0d, 0x0c,
    0x0b, 0x0a, 0x08, 0x07, 0x06, 0x06, 0x05, 0x04, 0x03, 0x03, 0x02, 0x02,
    0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
    0x03, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c, 0x0d, 0x0f,
    0x10, 0x11, 0x13, 0x15, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24,
    0x26, 0x28, 0x2b, 0x2d, 0x2f, 0x32, 0x34, 0x37, 0x39, 0x3c, 0x3f, 0x41,
    0x44, 0x47, 0x4a, 0x4d, 0x4f, 0x52, 0x55, 0x58, 0x5b, 0x5e, 0x61, 0x64,
    0x67, 0x6a, 0x6d, 0x70, 0x74, 0x77, 0x7a, 0x7d, 0x80, 0x83, 0x86, 0x89,
    0x8c, 0x90, 0x93, 0x96, 0x99, 0x9c, 0x9f, 0xa2, 0xa5, 0xa8, 0xab, 0xae,
    0xb1, 0xb3, 0xb6, 0xb9, 0xbc, 0xbf, 0xc1, 0xc4, 0xc7, 0xc9, 0xcc, 0xce,
    0xd1, 0xd3, 0xd5, 0xd8, 0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8,
    0xea, 0xeb, 0xed, 0xef, 0xf0, 0xf1, 0xf3, 0xf4, 0xf5, 0xf6, 0xf8, 0xf9,
    0xfa, 0xfa, 0xfb, 0xfc, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd, 0xfc, 0xfb, 0xfa,
    0xfa, 0xf9, 0xf8, 0xf6, 0xf5, 0xf4, 0xf3, 0xf1, 0xf0, 0xef, 0xed, 0xeb,
    0xea, 0xe8, 0xe6, 0xe4, 0xe2, 0xe0, 0xde, 0xdc, 0xda, 0xd8, 0xd5, 0xd3,
    0xd1, 0xce, 0xcc, 0xc9, 0xc7, 0xc4, 0xc1, 0xbf, 0xbc, 0xb9, 0xb6, 0xb3,
    0xb1, 0xae, 0xab, 0xa8, 0xa5, 0xa2, 0x9f, 0x9c, 0x99, 0x96, 0x93, 0x90,
    0x8c, 0x89, 0x86, 0x83};

static constexpr uint8_t NUM_COLORS = 16;

// Sets MEGA65 speed to 3.5 Mhz
static void speed_mode3() {
  CPU_PORTDDR &= ~1;             // clear 40 MHz override
  VICIV.ctrlb |= VIC3_FAST_MASK; // 3.5 MHz (C65 speed)
}

// Two-step VBlank sync: first ensure we're in the visible area,
// then wait for the next VBlank edge. This avoids the false-pass
// that occurs when the previous frame finishes during VBlank.
static void wait_vblank() {
  constexpr uint8_t RASTER_MSB = 0x80; // bit 7 of ctrl1: raster line >= 256
  while (VICIV.ctrl1 & RASTER_MSB)
    ;
  while (!(VICIV.ctrl1 & RASTER_MSB))
    ;
}

// Circular dithering matrix (values 0-63, 64=never lit). Pixels fill outward
// from center as growing dots; maximum fill is an inscribed circle with corners
// always empty. Quadrant-alternating tie-break prevents ring artifacts.
// clang-format off
static constexpr uint8_t circle8[8][8] = {
    {64, 64, 54, 40, 47, 59, 64, 64},
    {64, 52, 30, 20, 25, 35, 44, 64},
    {62, 37, 15,  5, 10, 17, 32, 57},
    {49, 27, 12,  0,  2,  7, 22, 42},
    {43, 23,  9,  4,  1, 14, 28, 51},
    {58, 33, 19, 11,  6, 16, 38, 63},
    {64, 46, 36, 26, 21, 31, 53, 64},
    {64, 64, 61, 48, 41, 56, 64, 64}
};
// clang-format on

// Generate charset with 256 circular-dithered characters at given address.
// Each character's fill density matches its sine_table entry, with pixels
// filling outward from center to form smooth circular gradients.
static void make_charset(const uint16_t charset_address) {
  auto charset = reinterpret_cast<volatile uint8_t *>(charset_address);
  for (const auto sine : sine_table) {
    // Invert so low sine = bright; shift to match circle8 range (0-63)
    const uint8_t threshold = (UINT8_MAX - sine) >> 2;
    for (uint8_t py = 0; py < 8; ++py) {
      uint8_t pattern = 0;
      for (uint8_t px = 0; px < 8; ++px) {
        if (circle8[py][px] < threshold)
          pattern |= (128 >> px);
      }
      *(charset++) = pattern;
    }
  }
}

// Plasma class
template <size_t COLS, size_t ROWS> class Plasma {
private:
  // 16 shades of blue for smooth palette cycling.
  struct PaletteGradient {
    std::array<uint8_t, NUM_COLORS> r{}, g{}, b{};

    // Palette register uses reversed-nybble encoding: replicate
    // 4-bit intensity into both nybbles for full brightness.
    static constexpr uint8_t nyb(uint8_t n) { return (n << 4) | n; }

    constexpr PaletteGradient() {
      for (uint8_t i = 0; i < NUM_COLORS; ++i) {
        r[i] = nyb(0);
        g[i] = nyb(i / 4);           // subtle cyan tint at bright end
        b[i] = nyb(i * 13 / 15 + 2); // dark navy (2) → bright blue (15)
      }
    }
  };

  static constexpr PaletteGradient gradient{};

  std::array<uint8_t, ROWS> ydata;
  std::array<uint8_t, COLS> xdata;
  std::array<uint8_t, COLS * ROWS>
      color_buf; // DMA-copied to color RAM each frame
  uint8_t x_cnt1 = 0;
  uint8_t x_cnt2 = 0;
  uint8_t y_cnt1 = 0;
  uint8_t y_cnt2 = 0;
  uint8_t palette_offset = 0;

  // Write rotated gradient to palette RAM entries 1-15.
  // Entry 0 stays black (used by border and screen background).
  void rotate_palette() {
    for (uint8_t i = 1; i < NUM_COLORS; ++i) {
      const uint8_t idx = (i + palette_offset) & (NUM_COLORS - 1);
      PALETTE.red[i] = gradient.r[idx];
      PALETTE.green[i] = gradient.g[idx];
      PALETTE.blue[i] = gradient.b[idx];
    }
    ++palette_offset;
  }

public:
  // Generate and activate charset at given address
  Plasma(const uint16_t charset_address) {
    make_charset(charset_address);
    VICIV.charptr = charset_address;
  }

  // Draw frame
  inline void update() {
    auto i = y_cnt1;
    auto j = y_cnt2;
    for (auto &y : ydata) {
      y = sine_table[i] + sine_table[j];
      i += 4;
      j += 9;
    }
    i = x_cnt1;
    j = x_cnt2;
    for (auto &x : xdata) {
      x = sine_table[i] + sine_table[j];
      i += 3;
      j += 7;
    }
    // Asymmetric increments create non-repeating interference patterns
    x_cnt1 += 2;
    x_cnt2 -= 3;
    y_cnt1 += 3;
    y_cnt2 -= 5;

    rotate_palette(); // update palette while raster is in VBlank
    write_to_screen();
  }

  // Write summed buffers to screen memory and update color RAM via DMA.
  // Color RAM lives at $0FF80000 — outside the CPU's 16-bit address
  // space — so we build a buffer and DMA copy it each frame.
  inline void write_to_screen() {
    auto screen_ptr = reinterpret_cast<volatile uint8_t *>(&DEFAULT_SCREEN);
    auto color_ptr = color_buf.data();
    for (const auto y : ydata) {
#pragma unroll 8 // reduce loop overhead without excessive code bloat
      for (const auto x : xdata) {
        const uint8_t sum = y + x;
        *(screen_ptr++) = sum; // character index into dithered charset
        *(color_ptr++) = sum / NUM_COLORS; // map to palette entry 0-15
      }
    }
    constexpr uint32_t COLOR_RAM_ADDR = 0x0FF80000UL; // 28-bit DMA address
    static const auto dma = make_dma_copy(
        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(color_buf.data())),
        COLOR_RAM_ADDR, COLS * ROWS);
    trigger_dma(dma);
  }
};

int main() {
  constexpr size_t COLS = 80;
  constexpr size_t ROWS = 25;
  constexpr uint16_t CHARSET_ADDRESS = 0x3000;
  Plasma<COLS, ROWS> plasma(CHARSET_ADDRESS);

  constexpr uint8_t VICIV_KEY1 = 0x47; // VIC-IV unlock knock sequence
  constexpr uint8_t VICIV_KEY2 = 0x53;

  // Prevent KERNAL IRQ handler from relocking VIC-IV register state.
  asm volatile("sei");

  // Unlock VIC-IV registers for palette RAM access
  VICIV.key = VICIV_KEY1;
  VICIV.key = VICIV_KEY2;

  // Use palette RAM for colors 0-15 (16+ always use palette RAM)
  VICIV.ctrla |= VIC3_PAL_MASK;

  // Black border and background — palette entry 0 is never rotated.
  VICIV.bordercol = 0;
  VICIV.screencol = 0;
  PALETTE.red[0] = 0;
  PALETTE.green[0] = 0;
  PALETTE.blue[0] = 0;

  speed_mode3();

  while (true) {
    wait_vblank();
    plasma.update();
  }
}
