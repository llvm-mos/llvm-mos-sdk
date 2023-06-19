/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_JOYPAD_H_
#define _PCE_JOYPAD_H_

#include <stdbool.h>
#include <stdint.h>

/** \file joypad.h
 * Functionality related to the joypad.
 */

#define KEY_LEFT	0x80
#define KEY_RIGHT	0x40
#define KEY_DOWN	0x20
#define KEY_UP		0x10
#define KEY_RUN		0x08
#define KEY_SELECT	0x04
#define KEY_2		0x02
#define KEY_1		0x01

/**
 * @brief Write a value to the joypad I/O port.
 * 
 * @param value The value to write.
 * @return uint8_t The returned value.
 */
uint8_t pce_joypad_io(uint8_t value);

/**
 * @brief Read the first joypad controller's pressed buttons.
 * 
 * @return uint8_t Buttons currently pressed.
 */
uint8_t pce_joypad_read(void);

/**
 * @brief Read the next joypad controller's pressed buttons.
 *
 * If a multitap is to be used, one should use this function for all
 * controllers after the first one (which should use @ref pce_joypad_read
 * instead).
 * 
 * @return uint8_t Buttons currently pressed.
 */
uint8_t pce_joypad_next(void);

#endif /* _PCE_JOYPAD_H_ */