/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_VDC_H_
#define _PCE_VDC_H_

#include <stdbool.h>
#include <stdint.h>

/** \file vdc.h
 * Functionality related to the VDC.
 */

uint16_t pce_vdc_reg_read(uint8_t index);
void pce_vdc_reg_write(uint8_t index, uint16_t data);

#endif /* _PCE_VDC_H_ */