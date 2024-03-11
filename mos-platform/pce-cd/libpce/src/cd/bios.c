/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include "pce/cd/bios.h"
#include "pce/cd/types.h"
#include "pce/hardware.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* PCE CD BIOS calling convention */

#define ASM_BIOSCALL(index) "jsr 0xE000 + ((" #index ") * 3)\n"
#define __irq_flags ((volatile uint8_t *)0x20F5)
#define __vram_write_flag ((volatile uint8_t *)0x2272)
#define __ax ((volatile uint16_t *)0x20F8)
#define __al ((volatile uint8_t *)0x20F8)
#define __ah ((volatile uint8_t *)0x20F9)
#define __bx ((volatile uint16_t *)0x20FA)
#define __bl ((volatile uint8_t *)0x20FA)
#define __bh ((volatile uint8_t *)0x20FB)
#define __cx_dx ((volatile uint32_t *)0x20FC)
#define __cx ((volatile uint16_t *)0x20FC)
#define __cl ((volatile uint8_t *)0x20FC)
#define __ch ((volatile uint8_t *)0x20FD)
#define __dx ((volatile uint16_t *)0x20FE)
#define __dl ((volatile uint8_t *)0x20FE)
#define __dh ((volatile uint8_t *)0x20FF)
#define __satb_addr ((volatile uint16_t *)0x2214)
#define __color_cmd ((volatile uint8_t *)0x221F)
#define __color_bgc_addr ((volatile uint16_t *)0x2220)
#define __color_bgc_length ((volatile uint8_t *)0x2222)
#define __color_sprc_addr ((volatile uint16_t *)0x2223)
#define __color_sprc_length ((volatile uint8_t *)0x2225)

bool pce_cdb_vram_in_use(void) { return *__vram_write_flag != 0; }

__attribute__((noreturn)) void pce_cdb_start(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x00));
}

uint8_t pce_cdb_cd_reset(void) {
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x01)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

void pce_cdb_cd_base(pce_sector_t base, uint8_t mode) {
  *__al = base.hi;
  *__ah = base.md;
  *__bl = base.lo;
  *__bh = mode;
  *__cl = mode;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x02)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

uint8_t pce_cdb_cd_read(pce_sector_t sector, uint8_t address_type,
                        uint16_t address, uint16_t length) {
  *__cl = sector.hi;
  *__ch = sector.md;
  *__dl = sector.lo;
  *__dh = address_type;
  *__bx = address;
  *__ax = length;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x03)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

void pce_cdb_cd_seek(pce_sector_t sector) {
  *__cl = sector.hi;
  *__ch = sector.md;
  *__dl = sector.lo;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x04)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

__attribute__((noreturn)) void pce_cdb_cd_exec(pce_sector_t sector,
                                               uint8_t address_type,
                                               uint16_t address,
                                               uint16_t length) {
  *__cl = sector.hi;
  *__ch = sector.md;
  *__dl = sector.lo;
  *__dh = address_type;
  *__bx = address;
  *__ax = length;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x05)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

uint8_t pce_cdb_cdda_play(uint8_t start_type, pce_sector_t start,
                          uint8_t end_type, pce_sector_t end, uint8_t mode) {
  *__al = start.hi;
  *__ah = start.md;
  *__bl = start.lo;
  *__bh = start_type;
  *__cl = end.hi;
  *__ch = end.md;
  *__dl = end.lo;
  *__dh = end_type | mode;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x06)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_cdda_search(pce_sector_t sector, uint8_t mode) {
  *__al = sector.hi;
  *__ah = sector.md;
  *__bl = sector.lo;
  *__bh = mode;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x07)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_cdda_pause(void) {
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x08)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

static uint8_t pce_cdb_cd_status(uint8_t mode) {
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x09)
                                     : "=a"(result)
                                     : "a"(mode)
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_cd_busy(void) { return pce_cdb_cd_status(0); }

uint8_t pce_cdb_cd_not_ready(void) { return pce_cdb_cd_status(1); }

uint8_t pce_cdb_cdda_read_subcode_q(pce_cdb_subq_data_t *buffer) {
  *__bx = (uint16_t)buffer;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x0A)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

static uint8_t pce_cdb_cd_read_toc(pce_cdb_toc_data_t *buffer, uint8_t type) {
  *__bx = (uint16_t)buffer;
  *__al = type;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x0B)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_cd_read_toc_track_count(pce_cdb_toc_data_t *buffer) {
  return pce_cdb_cd_read_toc(buffer, 0x00);
}

uint8_t pce_cdb_cd_read_toc_lead_out_time(pce_cdb_toc_data_t *buffer) {
  return pce_cdb_cd_read_toc(buffer, 0x01);
}

uint8_t pce_cdb_cd_read_toc_track_time(pce_cdb_toc_data_t *buffer,
                                       uint8_t track_id) {
  *__ah = track_id;
  return pce_cdb_cd_read_toc(buffer, 0x02);
}

uint8_t pce_cdb_cd_read_toc_track_sector(pce_cdb_toc_data_t *buffer,
                                         uint8_t track_id) {
  *__ah = track_id;
  return pce_cdb_cd_read_toc(buffer, 0x03);
}

uint8_t pce_cdb_cd_scan(void) {
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x0C)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

bool pce_cdb_cd_read_subcode_bits(uint8_t *buffer) {
  uint8_t value;
  bool result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x0D)
                                     : "=a"(value), "=c"(result)
                                     :
                                     : "x", "y", "p");
  *buffer = value;
  return !result;
}

uint16_t pce_cdb_cdda_read_sample(uint8_t channel) {
  uint8_t x, y;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x0E)
                                     : "=x"(x), "=y"(y), "+a"(channel)
                                     :
                                     : "p");
  return (y << 8) | x;
}

void pce_cdb_fader(uint8_t mode) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x0F)
                                     : "=a"(mode)
                                     :
                                     : "x", "y", "p");
}

void pce_cdb_adpcm_reset(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x10)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

uint8_t pce_cdb_adpcm_read_from_cd(pce_sector_t sector, uint8_t length,
                                   uint16_t address) {
  *__cl = sector.hi;
  *__ch = sector.md;
  *__dl = sector.lo;
  *__al = length;
  *__dh = 0x00;
  *__bx = address;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x11)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_adpcm_read_next_cd(pce_sector_t sector, uint8_t length) {
  *__cl = sector.hi;
  *__ch = sector.md;
  *__dl = sector.lo;
  *__al = length;
  *__dh = 0x01;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x11)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_adpcm_write_to_ram(uint16_t source, uint8_t dest_type,
                                   uint16_t dest, uint16_t length) {
  *__cx = source;
  *__dh = dest_type;
  *__bx = dest;
  *__ax = length;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x12)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_adpcm_read_from_ram(uint8_t source_type, uint16_t source,
                                    uint16_t dest, uint16_t length) {
  *__cx = dest;
  *__dh = source_type;
  *__bx = source;
  *__ax = length;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x13)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_adpcm_play(uint16_t address, uint16_t length, uint8_t divider,
                           uint8_t mode) {
  *__bx = address;
  *__ax = length;
  *__dh = divider;
  *__dl = mode & 0xFE;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x14)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_adpcm_continue(uint8_t mode) {
  *__dl = mode | 0x01;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x14)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

uint8_t pce_cdb_adpcm_stream(pce_sector_t sector, pce_sector_t length,
                             uint8_t divider) {
  *__cl = sector.hi;
  *__ch = sector.md;
  *__dl = sector.lo;
  *__al = length.hi;
  *__ah = length.md;
  *__bl = length.lo;
  *__dh = divider;
  uint8_t result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x15)
                                     : "=a"(result)
                                     :
                                     : "x", "y", "p");
  return result;
}

void pce_cdb_adpcm_stop(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x16)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

uint16_t pce_cdb_adpcm_status(void) {
  uint8_t a, x;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x17)
                                     : "=a"(a), "=x"(x)
                                     :
                                     : "y", "p");
  return (x << 8) | a;
}

// TODO: Backup RAM support.

uint16_t pce_cdb_version(void) {
  uint8_t x, y;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x1E)
                                     : "=x"(x), "=y"(y)
                                     :
                                     : "a", "p");
  return (x << 8) | y;
}

void pce_cdb_irq_set(uint8_t type, void (*irq_handler)(void)) {
  uint16_t irq_handler_address = (uint16_t)irq_handler;
  uint8_t x = irq_handler_address;
  uint8_t y = irq_handler_address >> 8;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x1F)
                                     : "+a"(type), "+x"(x), "+y"(y)
                                     :
                                     : "p");
}

void pce_cdb_irq_enable(uint8_t mask) { *__irq_flags |= mask; }

void pce_cdb_irq_disable(uint8_t mask) { *__irq_flags &= ~mask; }

// TODO: Kanji ROM support.

// TODO: Joypad support.

void pce_cdb_vdc_bg_set_size(uint8_t size) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x23)
                                     : "+a"(size)
                                     :
                                     : "x", "y", "p");
}

bool pce_cdb_vdc_set_resolution(uint8_t clock, uint8_t width_tiles,
                                uint8_t height_tiles) {
  bool result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x25)
                                     : "=c"(result), "+a"(clock),
                                       "+x"(width_tiles), "+y"(height_tiles)
                                     :
                                     : "p");
  return !result;
}

void pce_cdb_vdc_set_copy(uint8_t mode) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x26)
                                     : "+a"(mode)
                                     :
                                     : "x", "y", "p");
}

void pce_cdb_vdc_set_bg_column_copy(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x27)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_set_bg_row_copy(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x28)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_wait_vblank(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x29)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_irq_scanline_enable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x2A)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_irq_scanline_disable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x2B)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_irq_vblank_enable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x2C)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_irq_vblank_disable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x2D)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_bg_enable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x2E)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_bg_disable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x2F)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_sprite_enable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x30)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_sprite_disable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x31)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_bg_sprite_enable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x32)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_bg_sprite_disable(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x33)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_vram_configure_dma(uint8_t value) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x34)
                                     : "+a"(value)
                                     :
                                     : "x", "y", "p");
}

void pce_cdb_vdc_sprite_table_set_vram_addr(uint16_t address) {
  *__satb_addr = address;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x35)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_sprite_table_clear(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x36)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_sprite_table_put(void) {
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x37)
                                     :
                                     :
                                     : "a", "x", "y", "p");
}

void pce_cdb_vdc_irq_scanline_set(uint16_t line) {
  uint8_t a = line, x = line >> 8;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x38)
                                     : "+a"(a), "+x"(x)
                                     :
                                     : "y", "p");
}

void pce_cdb_vdc_vram_read_at(uint16_t addr) {
  uint8_t a = addr, x = addr >> 8;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x38)
                                     : "+a"(a), "+x"(x)
                                     :
                                     : "y", "p");
}

void pce_cdb_vdc_vram_write_at(uint16_t addr) {
  uint8_t a = addr, x = addr >> 8;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x38)
                                     : "+a"(a), "+x"(x)
                                     :
                                     : "y", "p");
}

uint8_t pce_cdb_bin_to_bcd(uint8_t value) {
  uint8_t result_value;
  bool result_flag;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x3C)
                                     : "=a"(result_value), "=c"(result_flag)
                                     :
                                     : "x", "y", "p");
  return result_flag ? 0xFF : result_value;
}

uint8_t pce_cdb_bcd_to_bin(uint8_t value) {
  uint8_t result_value;
  bool result_flag;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x3D)
                                     : "=a"(result_value), "=c"(result_flag)
                                     :
                                     : "x", "y", "p");
  return result_flag ? 0xFF : result_value;
}

uint16_t pce_cdb_mul_u8(uint8_t a, uint8_t b) {
  *__al = a;
  *__bl = b;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x3F)
                                     :
                                     :
                                     : "a", "x", "y", "p");
  return *__cx;
}

int16_t pce_cdb_mul_s8(int8_t a, int8_t b) {
  *__al = a;
  *__bl = b;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x40)
                                     :
                                     :
                                     : "a", "x", "y", "p");
  return *__cx;
}

uint32_t pce_cdb_mul_u16(uint16_t a, uint16_t b) {
  *__ax = a;
  *__bx = b;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x41)
                                     :
                                     :
                                     : "a", "x", "y", "p");
  return *__cx_dx;
}

pce_cdb_divmod_u16_result_t pce_cdb_divmod_u16(uint16_t a, uint16_t b) {
  *__ax = a;
  *__bx = b;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x42)
                                     :
                                     :
                                     : "a", "x", "y", "p");

  pce_cdb_divmod_u16_result_t result;
  result.quot = *__cx;
  result.rem = *__dx;
  return result;
}

pce_cdb_divmod_s16_result_t pce_cdb_divmod_s16(int16_t a, int16_t b) {
  *__ax = a;
  *__bx = b;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x43)
                                     :
                                     :
                                     : "a", "x", "y", "p");

  pce_cdb_divmod_s16_result_t result;
  result.quot = *__cx;
  result.rem = *__dx;
  return result;
}

uint8_t pce_cdb_sqrt(uint16_t a) {
  *__ax = a;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x44)
                                     :
                                     :
                                     : "a", "x", "y", "p");
  return *__cl;
}

// TODO: Trigonometric functions.

bool pce_cdb_ram_query(uint8_t *bank_start, uint8_t *bank_size) {
  uint8_t start, size;
  bool result;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x4A)
                                     : "=c"(result), "=a"(start), "=x"(size)
                                     :
                                     : "y", "p");
  if (bank_start != NULL)
    *bank_start = start;
  if (bank_size != NULL)
    *bank_size = size;
  return !result;
}

void pce_cdb_colors_bg_none(void) { *__color_bgc_length = 0; }

void pce_cdb_colors_bg_at(void *address, uint8_t count) {
  *__color_bgc_addr = (uint16_t)&address;
  *__color_bgc_length = (uint8_t)count;
}

void pce_cdb_colors_sprite_none(void) { *__color_sprc_length = 0; }

void pce_cdb_colors_sprite_at(void *address, uint8_t count) {
  *__color_sprc_addr = (uint16_t)&address;
  *__color_sprc_length = (uint8_t)count;
}

static bool pce_cdb_colors_cmd(uint8_t cmd) {
  if (*__color_cmd != 0x00)
    return false;
  *__color_cmd = cmd;
  __attribute__((leaf)) asm volatile(ASM_BIOSCALL(0x4C)
                                     :
                                     :
                                     : "a", "x", "y", "p");
  return true;
}

bool pce_cdb_colors_read(void) { return pce_cdb_colors_cmd(0x01); }

bool pce_cdb_colors_set(void) { return pce_cdb_colors_cmd(0x02); }

// TODO: PSG driver.
