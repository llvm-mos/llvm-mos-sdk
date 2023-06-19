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

/**
 * @brief Read a value from the VDC port.
 * 
 * @param index Register to read.
 * @return uint16_t Value read.
 */
uint16_t pce_vdc_peek(uint8_t index);

/**
 * @brief Write a value to the VDC port.
 * 
 * @param index Register to write.
 * @param data Value to write.
 */
void pce_vdc_poke(uint8_t index, uint16_t data);

#endif /* _PCE_VDC_H_ */