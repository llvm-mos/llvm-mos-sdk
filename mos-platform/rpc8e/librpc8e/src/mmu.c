/**
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

#include <stdint.h>
#include <rpc8e.h>

uint8_t rpc8e_redbus_map(uint8_t device_id) {
	uint8_t old_device = rpc8e_redbus_get_map();
	rpc8e_redbus_set_map(device_id);
	return old_device;
}

void rpc8e_redbus_set_map(uint8_t device_id) {
	__attribute__((leaf)) asm volatile(
		"mmu #$00"
		: "+a"(device_id) : : );
}

uint8_t rpc8e_redbus_get_map(void) {
	uint8_t result;
	__attribute__((leaf)) asm volatile(
		"mmu #$80"
		: "=a"(result) : : );
	return result;
}

void rpc8e_redbus_window_set_offset(uint16_t offset) {
	uint8_t offset_hi = offset >> 8;
	uint8_t offset_lo = offset;
	__attribute__((leaf)) asm volatile(
		"xba\n"
		"txa\n"
		"mmu #$01"
		: "+a"(offset_hi), "+x"(offset_lo) : : "p" );
}

uint16_t rpc8e_redbus_window_get_offset(void) {
	uint8_t result_hi, result_lo;
	__attribute__((leaf)) asm volatile(
		"mmu #$81\n"
		"txa\n"
		"xba"
		: "=a"(result_hi), "=x"(result_lo) : : "p" );
	return (((uint16_t) result_hi) << 8) | result_lo;
}

void rpc8e_redbus_enable(void) {
	__attribute__((leaf)) asm volatile("mmu #$02");
}

void rpc8e_redbus_disable(void) {
	__attribute__((leaf)) asm volatile("mmu #$82");
}

void rpc8e_mmu_ext_window_set(uint16_t value) {
	uint8_t value_hi = value >> 8;
	uint8_t value_lo = value;
	__attribute__((leaf)) asm volatile(
		"xba\n"
		"txa\n"
		"mmu #$03"
		: "+a"(value_hi), "+x"(value_lo) : : "p" );
}

uint16_t rpc8e_mmu_ext_window_get(void) {
	uint8_t result_hi, result_lo;
	__attribute__((leaf)) asm volatile(
		"mmu #$83\n"
		"txa\n"
		"xba"
		: "=a"(result_hi), "=x"(result_lo) : : "p" );
	return (((uint16_t) result_hi) << 8) | result_lo;
}

void rpc8e_mmu_ext_window_enable(void) {
	__attribute__((leaf)) asm volatile("mmu #$04");
}

void rpc8e_mmu_ext_window_disable(void) {
	__attribute__((leaf)) asm volatile("mmu #$84");
}

void rpc8e_mmu_set_brk_address(uint16_t addr) {
	uint8_t addr_hi = addr >> 8;
	uint8_t addr_lo = addr;
	__attribute__((leaf)) asm volatile(
		"xba\n"
		"txa\n"
		"mmu #$05"
		: "+a"(addr_hi), "+x"(addr_lo) : : "p" );
}

uint16_t rpc8e_mmu_get_brk_address(void) {
	uint8_t result_hi, result_lo;
	__attribute__((leaf)) asm volatile(
		"mmu #$85\n"
		"txa\n"
		"xba"
		: "=a"(result_hi), "=x"(result_lo) : : "p" );
	return (((uint16_t) result_hi) << 8) | result_lo;
}

void rpc8e_mmu_set_por_address(uint16_t addr) {
	uint8_t addr_hi = addr >> 8;
	uint8_t addr_lo = addr;
	__attribute__((leaf)) asm volatile(
		"xba\n"
		"txa\n"
		"mmu #$06"
		: "+a"(addr_hi), "+x"(addr_lo) : : "p" );
}

uint16_t rpc8e_mmu_get_por_address(void) {
	uint8_t result_hi, result_lo;
	__attribute__((leaf)) asm volatile(
		"mmu #$86\n"
		"txa\n"
		"xba"
		: "=a"(result_hi), "=x"(result_lo) : : "p" );
	return (((uint16_t) result_hi) << 8) | result_lo;
}
