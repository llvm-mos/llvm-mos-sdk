/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once
#include <stdint.h>

/** \file mmu.h
 * Functionality related to the MMU.
 */

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t boot_drive_id;
extern uint8_t boot_display_id;

void rpc8e_redbus_map(uint8_t device_id);
uint8_t rpc8e_redbus_get_map(void);
void rpc8e_redbus_window_set_offset(uint16_t offset);
uint16_t rpc8e_redbus_window_get_offset(void);
void rpc8e_redbus_enable(void);
void rpc8e_redbus_disable(void);
void rpc8e_mmu_ext_window_set(uint16_t addr);
uint16_t rpc8e_mmu_ext_window_get(void);
void rpc8e_mmu_ext_window_enable(void);
void rpc8e_mmu_ext_window_disable(void);
void rpc8e_mmu_set_brk_address(uint16_t addr);
uint16_t rpc8e_mmu_get_brk_address(void);
void rpc8e_mmu_set_por_address(uint16_t addr);
uint16_t rpc8e_mmu_get_por_address(void);

#ifdef __cplusplus
}
#endif
