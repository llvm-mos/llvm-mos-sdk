/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include "pce/hardware.h"
#include "pce/memory.h"

#define PCE_VDC_INDEX_CONST(index) \
	__attribute__((leaf)) asm volatile( \
		"st0 #%c0\n" : : "i"(index) \
	)

uint16_t pce_vdc_peek(uint8_t index) {
	*IO_VDC_INDEX = index;
	return *IO_VDC_DATA;
}

void pce_vdc_poke(uint8_t index, uint16_t data) {
	*IO_VDC_INDEX = index;
	*IO_VDC_DATA = data;
}

void pce_vdc_copy_to_vram(uint16_t dest, const void *source, uint16_t length) {
	PCE_VDC_INDEX_CONST(VDC_REG_VRAM_WRITE_ADDR); *IO_VDC_DATA = dest;
	PCE_VDC_INDEX_CONST(VDC_REG_VRAM_DATA);
	pce_memop(IO_VDC_DATA, source, length, PCE_MEMOP_INCR_ALT);
}

void pce_vdc_copy_from_vram(void *dest, uint16_t source, uint16_t length) {
	PCE_VDC_INDEX_CONST(VDC_REG_VRAM_READ_ADDR); *IO_VDC_DATA = source;
	PCE_VDC_INDEX_CONST(VDC_REG_VRAM_DATA);
	pce_memop(dest, IO_VDC_DATA, length, PCE_MEMOP_ALT_INCR);
}

static uint8_t hstart_offset_by_clock[] = {36, 48, 72};
static uint8_t vdc_cycles_by_clock[] = {VDC_CYCLE_8_SLOTS, VDC_CYCLE_4_SLOTS, VDC_CYCLE_4_SLOTS};

void pce_vdc_set_width_tiles(uint8_t tiles, uint8_t vce_flags) {
	uint8_t clock = (tiles <= 3) ? 0 : ((tiles <= 40) ? 1 : 2);
	uint8_t hstart = (hstart_offset_by_clock[clock] - tiles) >> 1;
	
	// Reset VCE clock to 5MHz.
	*IO_VCE_CONTROL = 0x00;

	// Set HDISP/HSYNC.
	PCE_VDC_INDEX_CONST(VDC_REG_TIMING_HSYNC); *IO_VDC_DATA = VDC_TIMING(hstart, 2);
	PCE_VDC_INDEX_CONST(VDC_REG_TIMING_HDISP); *IO_VDC_DATA = VDC_TIMING(4, tiles-1);

	// Set VDC cycles.
	PCE_VDC_INDEX_CONST(VDC_REG_MEMORY);
	*IO_VDC_DATA_LO = ((*IO_VDC_DATA_LO) & ~VDC_CYCLE_MASK) | vdc_cycles_by_clock[clock];

	// Set VCE clock to target speed.
	*IO_VCE_CONTROL = clock | vce_flags;
}

void pce_vdc_set_height(uint8_t lines) {
	uint8_t vstart = ((lines ^ 0xFF) >> 1) + 8;
	// Set VDISP/VSYNC.
	PCE_VDC_INDEX_CONST(VDC_REG_TIMING_VSYNC); *IO_VDC_DATA = VDC_TIMING(vstart, 2);
	PCE_VDC_INDEX_CONST(VDC_REG_TIMING_VDISP); *IO_VDC_DATA = lines - 1;
	PCE_VDC_INDEX_CONST(VDC_REG_TIMING_VDISPEND); *IO_VDC_DATA = 12;
}

void pce_vdc_set_bg_size(uint8_t value) {
	PCE_VDC_INDEX_CONST(VDC_REG_MEMORY);
	*IO_VDC_DATA_LO = ((*IO_VDC_DATA_LO) & ~VDC_BG_SIZE_MASK) | value;
}