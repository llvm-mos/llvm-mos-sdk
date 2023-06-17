/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _RPC8E_MMU_H_
#define _RPC8E_MMU_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file mmu.h
 * Functionality related to the MMU.
 */

extern uint8_t boot_drive_id;
extern uint8_t boot_display_id;

/**
 * @brief Map a given RedBus device ID to memory.
 *        Return the previous device's ID.
 *
 * @param device_id The device ID.
 * @return uint8_t The previous device ID.
 */
uint8_t rpc8e_redbus_map(uint8_t device_id);

/**
 * @brief Map a given RedBus device ID to memory.
 *
 * @param device_id The device ID.
 */
void rpc8e_redbus_set_map(uint8_t device_id);

/**
 * @brief Get the currently mapped RedBus device ID.
 *
 * @return uint8_t The current device ID.
 */
uint8_t rpc8e_redbus_get_map(void);

void rpc8e_redbus_window_set_offset(uint16_t offset);
uint16_t rpc8e_redbus_window_get_offset(void);

/**
 * @brief Enable the RedBus memory mapping.
 */
void rpc8e_redbus_enable(void);

/**
 * @brief Disable the RedBus memory mapping.
 */
void rpc8e_redbus_disable(void);

void rpc8e_mmu_ext_window_set(uint16_t addr);
uint16_t rpc8e_mmu_ext_window_get(void);
void rpc8e_mmu_ext_window_enable(void);
void rpc8e_mmu_ext_window_disable(void);

/**
 * @brief Set the BRK address.
 */
void rpc8e_mmu_set_brk_address(uint16_t addr);

/**
 * @brief Get the current BRK address.
 */
uint16_t rpc8e_mmu_get_brk_address(void);

/**
 * @brief Set the POR (power-on/reset) address.
 */
void rpc8e_mmu_set_por_address(uint16_t addr);

/**
 * @brief Get the current POR (power-on/reset) address.
 */
uint16_t rpc8e_mmu_get_por_address(void);

#ifdef __cplusplus
}
#endif

#endif /* _RPC8E_MMU_H_ */
