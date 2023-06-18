/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include "pce/hardware.h"

uint16_t pce_vdc_reg_read(uint8_t index) {
	*IO_VDC_INDEX = index;
	return *IO_VDC_DATA;
}

void pce_vdc_reg_write(uint8_t index, uint16_t data) {
	*IO_VDC_INDEX = index;
	*IO_VDC_DATA = data;
}
