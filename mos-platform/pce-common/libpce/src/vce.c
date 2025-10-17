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

uint16_t pce_vce_get_color(uint16_t index) {
  *IO_VCE_COLOR_INDEX = index;
  return *IO_VCE_COLOR_DATA;
}

void pce_vce_set_color(uint16_t index, uint16_t value) {
  *IO_VCE_COLOR_INDEX = index;
  *IO_VCE_COLOR_DATA = value;
}

void pce_vce_copy_palette(uint8_t index, const void *source, uint8_t count) {
  *IO_VCE_COLOR_INDEX = ((uint16_t)index) << 4;
  pce_memop((void *)IO_VCE_COLOR_DATA, source, ((uint16_t)count) << 5,
            PCE_MEMOP_INCR_ALT);
}

void pce_vce_copy_palette_to_ram(void *dest, uint8_t index, uint8_t count) {
  *IO_VCE_COLOR_INDEX = ((uint16_t)index) << 4;
  pce_memop(dest, (const void *)IO_VCE_COLOR_DATA, ((uint16_t)count) << 5,
            PCE_MEMOP_ALT_INCR);
}
