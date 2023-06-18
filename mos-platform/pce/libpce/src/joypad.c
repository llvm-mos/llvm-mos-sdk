/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include "pce/hardware.h"

uint8_t pce_joypad_io(uint8_t value) {
	uint8_t result;
	*IO_JOYPAD = value;
	__attribute__((leaf)) asm volatile("sxy\nsxy\nsxy\nsxy\n"); // burn cycles
	return *IO_JOYPAD;
}

__attribute__((noinline))
uint8_t pce_joypad_next(void) {
	uint8_t low = pce_joypad_io(0);
	uint8_t high = pce_joypad_io(JOYPAD_SEL);
	return (low & 0xF) | (high << 4);
}

uint8_t pce_joypad_read(void) {
	pce_joypad_io(JOYPAD_SEL);
	pce_joypad_io(JOYPAD_SEL | JOYPAD_CLR);
	return pce_joypad_next();
}
