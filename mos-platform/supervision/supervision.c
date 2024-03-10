/*
 * Copyright (c) 2024 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include <string.h>
#include "supervision.h"

__attribute__((section(".zp.bss"))) volatile uint8_t __sys_control;

uint8_t sv_sys_control_get(void) {
	return __sys_control;
}

void sv_sys_control_set(uint8_t value) {
	__sys_control = value;
	SV_SYS.control = value;
}

void sv_lcd_clear(void) {
	memset(SV_VRAM, 0, SV_VRAM_PITCH * SV_VRAM_HEIGHT);
}

void sv_lcd_enable(void) {
	SV_LCD.width = SV_LCD_WIDTH;
	SV_LCD.height = SV_LCD_HEIGHT;
	SV_LCD.x = 0;
	SV_LCD.y = 0;
	sv_sys_control_set(sv_sys_control_get() | SV_SYS_LCD_ENABLE);
}

void sv_lcd_disable(void) {
	sv_sys_control_set(sv_sys_control_get() & ~SV_SYS_LCD_ENABLE);
}

void sv_dma_to_vram(void *dest, const void *src, uint16_t len) {
	SV_VDMA.cpu = src;
	SV_VDMA.vram = SV_VDMA_TO_VRAM(dest);
	SV_VDMA.length = len >> 4;
	SV_VDMA.trigger = SV_TRIGGER_START;
	SV_VDMA.trigger = SV_TRIGGER_STOP;
}

void sv_dma_from_vram(void *dest, const void *src, uint16_t len) {
	SV_VDMA.cpu = dest;
	SV_VDMA.vram = SV_VDMA_FROM_VRAM(src);
	SV_VDMA.length = len >> 4;
	SV_VDMA.trigger = SV_TRIGGER_START;
	SV_VDMA.trigger = SV_TRIGGER_STOP;
}

uint8_t sv_bank_get(void) {
	return sv_sys_control_get() >> 5;
}

void sv_bank_set(uint8_t value) {
	sv_sys_control_set((value << 5) | (sv_sys_control_get() & 0x1F));
}
