// Copyright 2026 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.
//
// Rotating vector-line "LLVM-MOS" logo for MEGA65
//
// Renders the text "LLVM-MOS" as wireframe line segments on a 320x200
// hires bitmap, tumbling on all three axes with breathing zoom.
//
// MEGA65 features used:
//   - C64-compatible Bit Map Mode (BMM): 320x200, 1 bit/pixel
//   - Hardware math accelerator ($D768): 32x32 multiply for fixed-point
//     rotation (sin/cos applied to each vertex per frame)
//   - Enhanced DMA controller: fast 8KB bitmap clear each frame
//   - VIC-IV extended screen/char pointers: places bitmap in BSS
//     (avoids CIA2 bank tricks)
//   - 3.5 MHz C65 speed mode

#include <cstdint>
#include <dma.hpp>
#include <mega65.h>

using namespace mega65::dma;

// 8.8 fixed-point arithmetic
using fix16 = int16_t;

static constexpr uint16_t SCREEN_W = 320;
static constexpr uint16_t SCREEN_H = 200;
static constexpr uint8_t CELL_COLS = 40;
static constexpr uint8_t CELL_ROWS = 25;
static constexpr uint16_t SCREEN_RAM_SIZE =
    CELL_COLS * CELL_ROWS; // fg/bg color nybbles per 8x8 cell
static constexpr uint16_t CELL_ROW_BYTES = CELL_COLS * 8;
static constexpr uint16_t BITMAP_SIZE = CELL_ROW_BYTES * CELL_ROWS;
static constexpr uint16_t BITMAP_ALIGN = 8192;

// Compile-time sine table (256 entries, 8.8 fixed-point, one full period)
struct SineTable {
  fix16 v[256]{};
  constexpr SineTable() {
    // Quarter-wave with double-precision Taylor (7th order Horner form),
    // reflected to build all four quadrants. Double is fine here since
    // this runs entirely at compile time.
    constexpr double PI = 3.14159265358979323846;
    for (int i = 0; i <= 64; ++i) {
      double a = i * (PI / 2.0) / 64.0;
      double a2 = a * a;
      // sin(a) ~ a(1 - a^2/6(1 - a^2/20(1 - a^2/42)))
      double s = a * (1.0 - a2 / 6.0 * (1.0 - a2 / 20.0 * (1.0 - a2 / 42.0)));
      auto val = static_cast<fix16>(s * 256.0 + 0.5); // round to 8.8
      if (val > 256)
        val = 256;
      v[i] = val;                 // quadrant I
      v[128 - i] = val;           // quadrant II
      v[128 + i] = -val;          // quadrant III
      v[(256 - i) & 0xFF] = -val; // quadrant IV
    }
  }
};

static constexpr SineTable sin_tbl{};
static constexpr fix16 sin8(uint8_t angle) { return sin_tbl.v[angle]; }
static constexpr fix16 cos8(uint8_t angle) {
  return sin_tbl.v[(angle + 64) & 0xFF];
}

// Logo geometry: "LLVM-MOS" as vertices + segments
struct Vertex {
  int8_t x, y;
};
struct Segment {
  uint8_t v0, v1;
};

// NOLINTBEGIN
// clang-format off

// Each letter defined with vertices centered around a local origin,
// placed side-by-side with spacing. Total span: x in [-57,57], y in [-8,8].
static constexpr Vertex vertices[] = {
  // L (x offset -54)
  {-54,  -8}, {-54,   8}, {-46,   8},
  // L (x offset -42)
  {-42,  -8}, {-42,   8}, {-34,   8},
  // V (x offset -28)
  {-32,  -8}, {-28,   8}, {-24,  -8},
  // M (x offset -17)
  {-20,   8}, {-20,  -8}, {-14,   0}, {-8,  -8}, {-8,   8},
  // - (x offset -2)
  { -4,   0}, {  4,   0},
  // M (x offset 11)
  {  6,   8}, {  6,  -8}, { 12,   0}, { 18, -8}, { 18,  8},
  // O (x offset 25)
  { 22,  -8}, { 32,  -8}, { 32,   8}, { 22,   8},
  // S (x offset 40)
  { 46,  -8}, { 36,  -8}, { 36,   0}, { 46,   0}, { 46,   8}, { 36,   8},
};

static constexpr Segment segments[] = {
  {0, 1}, {1, 2},                             // L
  {3, 4}, {4, 5},                             // L
  {6, 7}, {7, 8},                             // V
  {9, 10}, {10, 11}, {11, 12}, {12, 13},      // M
  {14, 15},                                   // -
  {16, 17}, {17, 18}, {18, 19}, {19, 20},     // M
  {21, 22}, {22, 23}, {23, 24}, {24, 21},     // O
  {25, 26}, {26, 27}, {27, 28}, {28, 29}, {29, 30}, // S
};

// clang-format on
// NOLINTEND

// BMM rounds charptr down to 8KB boundary, so alignment is required.
static uint8_t bitmap[BITMAP_SIZE] __attribute__((aligned(BITMAP_ALIGN)));

// Screen RAM: each cell's nybbles set fg/bg color for its 8x8 block.
static uint8_t screen_ram[SCREEN_RAM_SIZE];

// Byte offset within bitmap for the leftmost pixel of each row.
// BMM uses the VIC-II interleaved layout: 8 consecutive bytes per 8x8 cell,
// cells arranged left-to-right then top-to-bottom (320 bytes per cell row).
struct RowTable {
  uint16_t v[SCREEN_H]{};
  constexpr RowTable() {
    for (uint16_t y = 0; y < SCREEN_H; ++y)
      v[y] = (y >> 3) * CELL_ROW_BYTES + (y & 7);
  }
};

static inline void plot_pixel(uint16_t x, uint16_t y) {
  static constexpr RowTable row_addr{};
  static constexpr uint8_t bit_mask[8] = {0x80, 0x40, 0x20, 0x10,
                                          0x08, 0x04, 0x02, 0x01};
  // Unsigned comparison catches negative values (they wrap to large positive)
  if (x >= SCREEN_W || y >= SCREEN_H)
    return;
  bitmap[row_addr.v[y] + (x & ~7)] |= bit_mask[x & 7];
}

// Bresenham line drawing: integer-only, X-major or Y-major branch
static void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t sx = 1, sy = 1;

  if (dx < 0) {
    dx = -dx;
    sx = -1;
  }
  if (dy < 0) {
    dy = -dy;
    sy = -1;
  }

  if (dx >= dy) {
    int16_t err = dx >> 1;
    for (int16_t i = 0; i <= dx; ++i) {
      plot_pixel(static_cast<uint16_t>(x0), static_cast<uint16_t>(y0));
      err -= dy;
      if (err < 0) {
        y0 += sy;
        err += dx;
      }
      x0 += sx;
    }
  } else {
    int16_t err = dy >> 1;
    for (int16_t i = 0; i <= dy; ++i) {
      plot_pixel(static_cast<uint16_t>(x0), static_cast<uint16_t>(y0));
      err -= dx;
      if (err < 0) {
        x0 += sx;
        err += dy;
      }
      y0 += sy;
    }
  }
}

// Hardware math accelerator
//
// The MEGA65 multiplier is combinational: the 64-bit product updates
// as soon as both 32-bit inputs are written. We split fp_mul into
// set/read helpers so the vertex loop can reuse whichever input
// register hasn't changed between consecutive multiplies.
static inline void fp_set_a(fix16 v) {
  MATH.multina32 = static_cast<int32_t>(v);
}

static inline void fp_set_b(fix16 v) {
  MATH.multinb32 = static_cast<int32_t>(v);
}

static inline fix16 fp_result() {
  asm volatile("" ::: "memory");
  return static_cast<fix16>(static_cast<int32_t>(MATH.multout32) >> 8);
}

static inline fix16 fp_mul(fix16 a, fix16 b) {
  fp_set_a(a);
  fp_set_b(b);
  return fp_result();
}

// VIC-IV setup for C64-compatible hires bitmap mode
static void setup_vic() {
  constexpr uint8_t VICIV_KEY1 = 0x47; // VIC-IV unlock knock sequence
  constexpr uint8_t VICIV_KEY2 = 0x53;
  constexpr uint8_t CELL_COLOR =
      0x86; // upper nybble = fg (orange), lower = bg (blue)

  asm volatile("sei");

  // Unlock VIC-IV registers
  VICIV.key = VICIV_KEY1;
  VICIV.key = VICIV_KEY2;

  // Disable hot registers for direct VIC-IV programming
  VICIV.sdbdrwd_msb &= ~VIC4_HOTREG_MASK;

  // 3.5 MHz C65 speed (no 40 MHz override via CPU_PORTDDR),
  // and disable VIC-III extended modes that would interfere
  CPU_PORTDDR &= ~1;
  VICIV.ctrlb =
      (VICIV.ctrlb | VIC3_FAST_MASK) & ~(VIC3_H640_MASK | VIC3_V400_MASK);

  // Point screen RAM to our array via extended pointers
  auto scrn = reinterpret_cast<uintptr_t>(screen_ram);
  VICIV.scrnptr_lsb = scrn & 0xFF;
  VICIV.scrnptr_msb = (scrn >> 8) & 0xFF;
  VICIV.scrnptr_bnk = 0x00;
  VICIV.scrnptr_mb = 0x00;

  // Point character/bitmap data to our aligned bitmap array
  auto bm = reinterpret_cast<uintptr_t>(bitmap);
  VICIV.charptr_lsb = bm & 0xFF;
  VICIV.charptr_msb = (bm >> 8) & 0xFF;
  VICIV.charptr_bnk = 0x00;

  // 40-column, 25-row screen geometry (320x200 in BMM)
  VICIV.linestep = CELL_COLS;
  VICIV.chrcount = CELL_COLS;
  VICIV.disp_rows = CELL_ROWS;

  // Enable bitmap mode: BMM=1, DEN=1, RSEL=1, YSCROLL=3
  VICIV.ctrl1 = 0x3B;
  // Hires (not multicolor): CSEL=1, XSCROLL=0
  VICIV.ctrl2 = 0x08;
  // No FCM features
  VICIV.ctrlc &= ~(VIC4_CHR16_MASK | VIC4_FCLRHI_MASK | VIC4_FCLRLO_MASK);

  VICIV.bordercol = COLOR_BLUE;
  VICIV.screencol = COLOR_BLUE;

  for (auto &cell : screen_ram)
    cell = CELL_COLOR;
}

// Two-step VBlank sync: wait for visible area, then wait for VBlank edge.
// Avoids false-pass when the previous frame finishes during VBlank.
static void wait_vblank() {
  constexpr uint8_t RASTER_MSB = 0x80;
  while (VICIV.ctrl1 & RASTER_MSB)
    ;
  while (!(VICIV.ctrl1 & RASTER_MSB))
    ;
}

static constexpr auto NUM_VERTS = sizeof(vertices) / sizeof(vertices[0]);
static int16_t screen_x[NUM_VERTS];
static int16_t screen_y[NUM_VERTS];

// Rotate, scale, and project all vertices to screen coordinates.
// Multiply ordering minimizes 32-bit MMIO writes by reusing whichever
// hardware math input register already holds the correct value.
static void transform_vertices(uint8_t spin, uint8_t tilt, uint8_t yaw,
                               fix16 scale) {
  constexpr fix16 FP_ONE = 256;
  const fix16 ss = sin8(spin);
  const fix16 cs = cos8(spin);
  const fix16 ct = cos8(tilt);
  const fix16 cy = cos8(yaw);

  for (size_t i = 0; i < NUM_VERTS; ++i) {
    const fix16 vx = static_cast<fix16>(vertices[i].x) * FP_ONE;
    const fix16 vy = static_cast<fix16>(vertices[i].y) * FP_ONE;

    // Tilt (X-axis): foreshorten Y by cos(tilt)
    fp_set_a(vy);
    fp_set_b(ct);
    const fix16 vy_t = fp_result();

    // Spin components of vy_t
    fp_set_a(vy_t);
    fp_set_b(cs);
    const fix16 vy_t_cs = fp_result();
    fp_set_b(ss);
    const fix16 vy_t_ss = fp_result();

    // Yaw (Y-axis): foreshorten X by cos(yaw)
    fp_set_a(vx);
    fp_set_b(cy);
    const fix16 vx_y = fp_result();

    // Spin components of vx_y
    fp_set_a(vx_y);
    fp_set_b(ss);
    const fix16 vx_y_ss = fp_result();
    fp_set_b(cs);
    const fix16 vx_y_cs = fp_result();

    // Combine spin rotation and scale to screen center
    const fix16 rx = vx_y_cs - vy_t_ss;
    const fix16 ry = vx_y_ss + vy_t_cs;

    fp_set_a(rx);
    fp_set_b(scale);
    screen_x[i] = (fp_result() >> 8) + (SCREEN_W / 2);

    fp_set_a(ry); // B=scale reused
    screen_y[i] = (fp_result() >> 8) + (SCREEN_H / 2);
  }
}

static void draw_segments() {
  for (const auto &seg : segments)
    draw_line(screen_x[seg.v0], screen_y[seg.v0], screen_x[seg.v1],
              screen_y[seg.v1]);
}

static void clear_bitmap() {
  static const auto dma =
      make_dma_fill(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(bitmap)),
                    0, BITMAP_SIZE);
  trigger_dma(dma);
}

int main() {
  setup_vic();

  // Scale factor: 540/256 ~ 2.1x in 8.8 fixed-point, fills ~75% of screen width
  constexpr fix16 SCALE = 540;
  // Breathing zoom amplitude (8.8), scale oscillates +/-BREATH_AMP around SCALE
  constexpr fix16 BREATH_AMP = 70;

  // 8.8 fixed-point accumulators: high byte = angle, low byte = fraction.
  // Coprime numerators ensure a long non-repeating tumble cycle.
  uint16_t spin_acc = 0;   // Z-axis: screen-plane spin
  uint16_t tilt_acc = 0;   // X-axis: around the logo's length axis
  uint16_t yaw_acc = 0;    // Y-axis: around the logo's height axis
  uint16_t breath_acc = 0; // breathing zoom oscillator

  while (true) {
    wait_vblank();
    clear_bitmap();

    const uint8_t spin = spin_acc >> 8;
    const uint8_t tilt = tilt_acc >> 8;
    const uint8_t yaw = yaw_acc >> 8;
    const uint8_t breath = breath_acc >> 8;

    // Breathing zoom: oscillate scale +/-BREATH_AMP around the base
    const fix16 scale = SCALE + fp_mul(sin8(breath), BREATH_AMP);

    transform_vertices(spin, tilt, yaw, scale);
    draw_segments();

    // Fractional increments: coprime numerators over 256
    // Full rotation periods: ~9s, ~12s, ~7s, ~16s at 50 fps
    spin_acc += 139;
    tilt_acc += 107;
    yaw_acc += 181;
    breath_acc += 79;
  }
}
