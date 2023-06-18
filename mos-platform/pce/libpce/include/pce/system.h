/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_SYSTEM_H_
#define _PCE_SYSTEM_H_

#include <stdbool.h>
#include <stdint.h>

/** \file system.h
 * Functionality related to the system.
 */

static inline void pce_cpu_irq_enable() {
	__attribute__((leaf)) asm volatile("cli\n");
}

static inline void pce_cpu_irq_disable() {
	__attribute__((leaf)) asm volatile("sei\n");
}

void pce_irq_enable(uint8_t mask);
void pce_irq_disable(uint8_t mask);

void pce_timer_init(uint8_t count);
void pce_timer_enable(void);
void pce_timer_disable(void);

#endif /* _PCE_SYSTEM_H_ */
