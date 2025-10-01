/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include "pce/hardware.h"
#include "pce/memory.h"
#include <stdint.h>

// The compiler should optimize away this value if it is not used.
// This way, non-SuperGrafx-using code doesn't have to pay the
// performance penalty for SuperGrafx support.
static volatile uint16_t *__vdc_base = 0x0000;

#undef IO_VDC_INDEX
#undef IO_VDC_DATA
#undef IO_VDC_DATA_LO
#undef IO_VDC_DATA_HI
// Using ORs here avoids having to carry a 16-bit add.
#define IO_VDC_INDEX ((volatile uint16_t *)__vdc_base)
#define IO_VDC_DATA ((volatile uint16_t *)((uint16_t)__vdc_base | 2))
#define IO_VDC_DATA_LO ((volatile uint8_t *)((uint16_t)__vdc_base | 2))
#define IO_VDC_DATA_HI ((volatile uint8_t *)((uint16_t)__vdc_base | 3))

#define PCE_VDC_INDEX_CONST(index)                                             \
  __attribute__((leaf)) asm volatile("st0 #%c0\n" : : "i"(index))
#define PCE_VDC_DATA_LO_CONST(index)                                           \
  __attribute__((leaf)) asm volatile("st1 #%c0\n" : : "i"(index))
#define PCE_VDC_DATA_HI_CONST(index)                                           \
  __attribute__((leaf)) asm volatile("st2 #%c0\n" : : "i"(index))

uint16_t pce_vdc_peek(uint8_t index) {
  *IO_VDC_INDEX = index;
  return *IO_VDC_DATA;
}

void pce_vdc_poke(uint8_t index, uint16_t data) {
  *IO_VDC_INDEX = index;
  *IO_VDC_DATA = data;
}

void pce_vdc_set_copy_word(void) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  PCE_VDC_DATA_HI_CONST(VDC_CONTROL_VRAM_ADD_1 >> 8);
}

void pce_vdc_set_copy_32_words(void) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  PCE_VDC_DATA_HI_CONST(VDC_CONTROL_VRAM_ADD_32 >> 8);
}

void pce_vdc_set_copy_64_words(void) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  PCE_VDC_DATA_HI_CONST(VDC_CONTROL_VRAM_ADD_64 >> 8);
}

void pce_vdc_set_copy_128_words(void) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  PCE_VDC_DATA_HI_CONST(VDC_CONTROL_VRAM_ADD_128 >> 8);
}

void pce_vdc_copy_to_vram(uint16_t dest, const void *source, uint16_t length) {
  PCE_VDC_INDEX_CONST(VDC_REG_VRAM_WRITE_ADDR);
  *IO_VDC_DATA = dest;
  PCE_VDC_INDEX_CONST(VDC_REG_VRAM_DATA);
  pce_memop((void *)IO_VDC_DATA, source, length, PCE_MEMOP_INCR_ALT);
}

void pce_vdc_copy_from_vram(void *dest, uint16_t source, uint16_t length) {
  PCE_VDC_INDEX_CONST(VDC_REG_VRAM_READ_ADDR);
  *IO_VDC_DATA = source;
  PCE_VDC_INDEX_CONST(VDC_REG_VRAM_DATA);
  pce_memop(dest, (const void *)IO_VDC_DATA, length, PCE_MEMOP_ALT_INCR);
}

void pce_vdc_dma_start(uint8_t mode, uint16_t source, uint16_t dest,
                       uint16_t length) {
  PCE_VDC_INDEX_CONST(VDC_REG_DMA_CONTROL);
  *IO_VDC_DATA_LO = mode;
  PCE_VDC_INDEX_CONST(VDC_REG_DMA_SRC);
  *IO_VDC_DATA = source;
  PCE_VDC_INDEX_CONST(VDC_REG_DMA_DEST);
  *IO_VDC_DATA = dest;
  PCE_VDC_INDEX_CONST(VDC_REG_DMA_LENGTH);
  *IO_VDC_DATA = length - 1;
}

bool pce_vdc_dma_finished(void) {
  PCE_VDC_INDEX_CONST(VDC_REG_DMA_LENGTH);
  return *IO_VDC_DATA == 0xFFFF;
}

static uint8_t vdc_memory_lo = 0;
static uint8_t vdc_control_lo = 0;
// static uint8_t vdc_control_hi = 0;
static const uint8_t hstart_offset_by_clock[] = {36, 51, 86};
static const uint8_t vdc_cycles_by_clock[] = {
    VDC_CYCLE_8_SLOTS, VDC_CYCLE_4_SLOTS, VDC_CYCLE_4_SLOTS};

static void __pce_vdc_init_vdc(void) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  *IO_VDC_DATA_LO = vdc_control_lo;
  PCE_VDC_DATA_HI_CONST(0);
  // *IO_VDC_DATA_HI = vdc_control_hi;
  PCE_VDC_INDEX_CONST(VDC_REG_BG_SCROLL_X);
  PCE_VDC_DATA_LO_CONST(0);
  PCE_VDC_DATA_HI_CONST(0);
  PCE_VDC_INDEX_CONST(VDC_REG_BG_SCROLL_Y);
  PCE_VDC_DATA_LO_CONST(0);
  PCE_VDC_DATA_HI_CONST(0);
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  *IO_VDC_DATA_LO = vdc_memory_lo;
  PCE_VDC_DATA_HI_CONST(0);
}

void __pce_vdc_init(void) {
  *IO_VCE_CONTROL = 0;

  __pce_vdc_init_vdc();

  *IO_VCE_COLOR_INDEX = 0;
  for (uint16_t i = 0; i < 0x200; i++) {
    *IO_VCE_COLOR_DATA = 0;
  }
}

void pce_vdc_set_width_tiles(uint8_t tiles, uint8_t vce_flags) {
  uint8_t clock = (tiles <= 32) ? 0 : ((tiles <= 40) ? 1 : 2);
  uint8_t hstart = (hstart_offset_by_clock[clock] - tiles) >> 1;

  // Reset VCE clock to 5MHz.
  *IO_VCE_CONTROL = 0x00;

  // Set HDISP/HSYNC.
  PCE_VDC_INDEX_CONST(VDC_REG_TIMING_HSYNC);
  PCE_VDC_DATA_LO_CONST(2);
  *IO_VDC_DATA_HI = hstart;
  PCE_VDC_INDEX_CONST(VDC_REG_TIMING_HDISP);
  *IO_VDC_DATA_LO = tiles - 1;
  PCE_VDC_DATA_HI_CONST(4);

  // Set VDC cycles.
  vdc_memory_lo =
      (vdc_memory_lo & ~VDC_CYCLE_MASK) | vdc_cycles_by_clock[clock];
  PCE_VDC_INDEX_CONST(VDC_REG_MEMORY);
  *IO_VDC_DATA_LO = vdc_memory_lo;

  // Set VCE clock to target speed.
  *IO_VCE_CONTROL = clock | vce_flags;
}

void pce_vdc_set_height(uint8_t lines) {
  uint8_t vstart = ((lines ^ 0xFF) >> 1) + 8;
  // Set VDISP/VSYNC.
  PCE_VDC_INDEX_CONST(VDC_REG_TIMING_VSYNC);
  PCE_VDC_DATA_LO_CONST(2);
  *IO_VDC_DATA_HI = vstart;
  PCE_VDC_INDEX_CONST(VDC_REG_TIMING_VDISP);
  *IO_VDC_DATA_LO = lines - 1;
  PCE_VDC_DATA_HI_CONST(0);
  PCE_VDC_INDEX_CONST(VDC_REG_TIMING_VDISPEND);
  PCE_VDC_DATA_LO_CONST(12);
  PCE_VDC_DATA_HI_CONST(0);
}

void pce_vdc_bg_set_size(uint8_t value) {
  PCE_VDC_INDEX_CONST(VDC_REG_MEMORY);
  vdc_memory_lo = (vdc_memory_lo & ~VDC_BG_SIZE_MASK) | value;
  *IO_VDC_DATA_LO = vdc_memory_lo;
}

void pce_vdc_sprite_set_table_start(uint16_t loc) {
  PCE_VDC_INDEX_CONST(VDC_REG_SATB_START);
  *IO_VDC_DATA = loc;
}

void pce_vdc_enable(uint8_t value) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  vdc_control_lo = vdc_control_lo | value;
  *IO_VDC_DATA_LO = vdc_control_lo;
}

void pce_vdc_disable(uint8_t value) {
  PCE_VDC_INDEX_CONST(VDC_REG_CONTROL);
  vdc_control_lo = vdc_control_lo & ~value;
  *IO_VDC_DATA_LO = vdc_control_lo;
}

bool pce_sgx_detect(void) {
  uint8_t value = *IO_VPC_CONTROL_HI; // unmapped on non-SGX
  *IO_VPC_CONTROL_HI ^=
      0xC0; // toggle only priority values to minimize glitching
  if (*IO_VPC_CONTROL_HI == value) {
    return false;
  } else {
    *IO_VPC_CONTROL_HI ^= 0xC0;
    return true;
  }
}

void pce_sgx_vdc1_set(void) {
  __vdc_base = (volatile uint16_t *)0x0000;
  *IO_VPC_PORT = VPC_PORT_VDP1;
}

void pce_sgx_vdc2_set(void) {
  __vdc_base = (volatile uint16_t *)0x0010;
  *IO_VPC_PORT = VPC_PORT_VDP2;
}

void pce_sgx_vdc_init(void) {
  pce_sgx_vdc2_set();
  __pce_vdc_init_vdc();
  pce_sgx_vdc1_set();
}

void pce_sgx_vdc_set(uint8_t id) {
  __vdc_base = (volatile uint16_t *)(id << 4);
  *IO_VPC_PORT = id;
}

volatile uint8_t *pce_sgx_vdc_get_index() {
  return (volatile uint8_t *)IO_VDC_INDEX;
}

volatile uint16_t *pce_sgx_vdc_get_data() { return IO_VDC_DATA; }

// Helper aliases.

void pce_vdc_set_copy_row(void) { pce_vdc_set_copy_word(); }

void pce_vdc_set_copy_column_32(void) { pce_vdc_set_copy_32_words(); }

void pce_vdc_set_copy_column_64(void) { pce_vdc_set_copy_64_words(); }

void pce_vdc_set_copy_column_128(void) { pce_vdc_set_copy_128_words(); }

void pce_vdc_set_width(uint16_t pixels, uint8_t vce_flags) {
  pce_vdc_set_width_tiles((pixels) >> 3, vce_flags);
}

void pce_vdc_set_resolution(uint16_t width_pixels, uint8_t height_pixels,
                            uint8_t vce_flags) {
  pce_vdc_set_width(width_pixels, vce_flags);
  pce_vdc_set_height(height_pixels);
}

void pce_vdc_bg_enable(void) { pce_vdc_enable(VDC_CONTROL_ENABLE_BG); }

void pce_vdc_bg_disable(void) { pce_vdc_disable(VDC_CONTROL_ENABLE_BG); }

void pce_vdc_sprite_enable(void) { pce_vdc_enable(VDC_CONTROL_ENABLE_SPRITE); }

void pce_vdc_sprite_disable(void) {
  pce_vdc_disable(VDC_CONTROL_ENABLE_SPRITE);
}

void pce_vdc_irq_scanline_enable(void) {
  pce_vdc_enable(VDC_CONTROL_IRQ_SCANLINE);
}

void pce_vdc_irq_scanline_disable(void) {
  pce_vdc_disable(VDC_CONTROL_IRQ_SCANLINE);
}

void pce_vdc_irq_sprite_collide_enable(void) {
  pce_vdc_enable(VDC_CONTROL_IRQ_SPRITE_COLLIDE);
}

void pce_vdc_irq_sprite_collide_disable(void) {
  pce_vdc_disable(VDC_CONTROL_IRQ_SPRITE_COLLIDE);
}

void pce_vdc_irq_sprite_overflow_enable(void) {
  pce_vdc_enable(VDC_CONTROL_IRQ_SPRITE_OVERFLOW);
}

void pce_vdc_irq_sprite_overflow_disable(void) {
  pce_vdc_disable(VDC_CONTROL_IRQ_SPRITE_OVERFLOW);
}

void pce_vdc_irq_vblank_enable(void) { pce_vdc_enable(VDC_CONTROL_IRQ_VBLANK); }

void pce_vdc_irq_vblank_disable(void) {
  pce_vdc_disable(VDC_CONTROL_IRQ_VBLANK);
}
