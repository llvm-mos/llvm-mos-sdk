/*
 * Copyright (c) 2024 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>

#ifndef _SUPERVISION_H
#define _SUPERVISION_H

#ifdef __cplusplus
extern "C" {
#endif

#define SV_SYSTEM_CLOCK_HZ 4000000
#define SV_LCD_WIDTH 160
#define SV_LCD_HEIGHT 160

#define SV_TRIGGER_START 0x80
#define SV_TRIGGER_STOP  0x00

struct __sv_lcd {
	uint8_t width;
	uint8_t height;
	uint8_t x;
	uint8_t y;
};
#define SV_LCD (*(volatile struct __sv_lcd*) 0x2000)

struct __sv_vdma {
	const void *cpu;
	uint16_t vram;
	uint8_t length;
	uint8_t trigger;
};
#define SV_VDMA (*(volatile struct __sv_vdma*) 0x2008)
#define SV_VDMA_FROM_VRAM(addr)  ((uint16_t) (addr))
#define SV_VDMA_TO_VRAM(addr)   (((uint16_t) (addr)) | 0x4000)

struct __sv_tone {
	uint16_t divider;
	uint8_t control;
	uint8_t length;
};
#define SV_AUDIO_TONE_R (*(volatile struct __sv_tone*) 0x2010)
#define SV_AUDIO_TONE_L (*(volatile struct __sv_tone*) 0x2014)

#define SV_AUDIO_TONE_REPEAT    0x40
#define SV_AUDIO_TONE_ONESHOT   0x00
#define SV_AUDIO_TONE_DUTY_12_5 0x00
#define SV_AUDIO_TONE_DUTY_25   0x10
#define SV_AUDIO_TONE_DUTY_50   0x20
#define SV_AUDIO_TONE_DUTY_75   0x30
#define SV_AUDIO_TONE_VOLUME(n) (n)

struct __sv_noise {
	uint8_t voldiv;
	uint8_t length;
	uint8_t control;
};
#define SV_AUDIO_NOISE (*(volatile strut __sv_noise*) 0x2028)

#define SV_AUDIO_NOISE_DIV_8     0x00
#define SV_AUDIO_NOISE_DIV_16    0x01
#define SV_AUDIO_NOISE_DIV_32    0x02
#define SV_AUDIO_NOISE_DIV_64    0x03
#define SV_AUDIO_NOISE_DIV_128   0x04
#define SV_AUDIO_NOISE_DIV_256   0x05
#define SV_AUDIO_NOISE_DIV_512   0x06
#define SV_AUDIO_NOISE_DIV_1024  0x07
#define SV_AUDIO_NOISE_DIV_2048  0x08
#define SV_AUDIO_NOISE_DIV_4096  0x09
#define SV_AUDIO_NOISE_DIV_8192  0x0A
#define SV_AUDIO_NOISE_DIV_16384 0x0B
#define SV_AUDIO_NOISE_DIV_32768 0x0C
#define SV_AUDIO_NOISE_DIV_65536 0x0D

#define SV_AUDIO_NOISE_ENABLE  0x10
#define SV_AUDIO_NOISE_LEFT    0x08
#define SV_AUDIO_NOISE_RIGHT   0x04
#define SV_AUDIO_NOISE_MONO    0x0C
#define SV_AUDIO_NOISE_REPEAT  0x02
#define SV_AUDIO_NOISE_ONESHOT 0x00
#define SV_AUDIO_NOISE_TAP_15  0x01
#define SV_AUDIO_NOISE_TAP_7   0x00

struct __sv_adma {
	const void *src;
	uint8_t length;
	uint8_t control;
	uint8_t trigger;
};
#define SV_AUDIO_DMA (*(volatile struct __sv_adma*) 0x2018)

#define SV_AUDIO_DMA_BANK(n)  ((n) << 4)
#define SV_AUDIO_DMA_LEFT     0x08
#define SV_AUDIO_DMA_RIGHT    0x04
#define SV_AUDIO_DMA_MONO     0x0C
#define SV_AUDIO_DMA_DIV_256  0x00
#define SV_AUDIO_DMA_DIV_512  0x01
#define SV_AUDIO_DMA_DIV_1024 0x02
#define SV_AUDIO_DMA_DIV_2048 0x03

#define SV_JOY (*(volatile uint8_t *) 0x2020)
#define SV_JOY_START  0x80
#define SV_JOY_SELECT 0x40
#define SV_JOY_A      0x20
#define SV_JOY_B      0x10
#define SV_JOY_UP     0x08
#define SV_JOY_DOWN   0x04
#define SV_JOY_LEFT   0x02
#define SV_JOY_RIGHT  0x01

struct __sv_link {
	uint8_t data;
	uint8_t dir;
};
#define SV_LINK (*(volatile struct __sv_link*) 0x2021)

struct __sv_sys {
	uint8_t timer_divider;
	uint8_t irq_timer_ack;
	uint8_t irq_audio_dma_ack;
	uint8_t control;
	uint8_t irq_status;
};
#define SV_SYS (*(volatile struct __sv_sys*) 0x2023)

#define SV_IRQ_STATUS_TIMER     0x01
#define SV_IRQ_STATUS_AUDIO_DMA 0x02

#define SV_SYS_NMI_ENABLE            0x01
#define SV_SYS_NMI_DISABLE           0x00
#define SV_SYS_IRQ_TIMER_ENABLE      0x02
#define SV_SYS_IRQ_TIMER_DISABLE     0x00
#define SV_SYS_IRQ_AUDIO_DMA_ENABLE  0x04
#define SV_SYS_IRQ_AUDIO_DMA_DISABLE 0x00
#define SV_SYS_LCD_ENABLE            0x08
#define SV_SYS_LCD_DISABLE           0x00
#define SV_SYS_TIMER_PRESCALER_256   0x00
#define SV_SYS_TIMER_PRESCALER_16384 0x10
#define SV_SYS_BANK_MASK             0xE0
#define SV_SYS_BANK(n)               ((n) << 5)

#define SV_RAM        ((uint8_t*) 0x0000)
#define SV_VRAM       ((uint8_t*) 0x4000)
#define SV_ROM        ((uint8_t*) 0x8000)
#define SV_ROM_FIXED  ((uint8_t*) 0xC000)

#define SV_VRAM_WIDTH 192
#define SV_VRAM_HEIGHT 170
#define SV_VRAM_PITCH 48
#define SV_VRAM_ROW(y) ((uint8_t*) (0x4000 + ((y) * SV_VRAM_PITCH)))

#define SV_COLOR_WHITE      0x00
#define SV_COLOR_LIGHT_GREY 0x01
#define SV_COLOR_DARK_GREY  0x02
#define SV_COLOR_BLACK      0x03

uint8_t sv_sys_control_get(void);
void sv_sys_control_set(uint8_t value);
void sv_lcd_clear(void);
void sv_lcd_enable(void);
void sv_lcd_disable(void);
void sv_dma_to_vram(void *dest, const void *src, uint16_t len);
void sv_dma_from_vram(void *dest, const void *src, uint16_t len);

/**
 * @brief Call a function from the given $8000-$BFFF bank.
 *
 * @param bank_id The bank ID to use.
 * @param method The method to call.
 */
__attribute__((leaf, callback(2))) void banked_call(uint8_t bank_id,
                                                    void (*method)(void));
__attribute__((leaf)) uint8_t sv_bank_get(void);
__attribute__((leaf)) void sv_bank_set(uint8_t id);

#define SV_CART_ROM_KB(kb) \
	asm(".globl __cart_rom_size\n__cart_rom_size = " #kb)

#ifdef __cplusplus
}
#endif

#endif
