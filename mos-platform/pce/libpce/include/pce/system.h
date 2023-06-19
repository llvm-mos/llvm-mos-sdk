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

/**
 * @brief Enable the specified IRQs.
 *
 * Note that one must enable IRQs on the CPU for this to be effective; the
 * console is initialized with IRQs disabled - see @ref pce_cpu_irq_enable .
 * 
 * @param mask The IRQ mask to enable.
 */
void pce_irq_enable(uint8_t mask);
/**
 * @brief Disable the specified IRQs.
 * 
 * @param mask The IRQ mask to disable.
 */
void pce_irq_disable(uint8_t mask);

/**
 * @brief Initialize the timer with a given reload value.
 *
 * To calculate the reload value's resulting frequency, use the following
 * equation:
 *
 * Frequency ~= 6992 / (N + 1) Hz
 *
 * This function does not enable the timer automatically.
 *
 * @param count The reload value.
 */
void pce_timer_set(uint8_t count);

/**
 * @brief Enable the timer.
 */
void pce_timer_enable(void);

/**
 * @brief Disable the timer.
 */
void pce_timer_disable(void);

/**
 * @brief Enable IRQs on the CPU.
 */
static inline void pce_cpu_irq_enable() {
	__attribute__((leaf)) asm volatile("cli\n");
}

/**
 * @brief Disable IRQs on the CPU.
 */
static inline void pce_cpu_irq_disable() {
	__attribute__((leaf)) asm volatile("sei\n");
}

#endif /* _PCE_SYSTEM_H_ */
