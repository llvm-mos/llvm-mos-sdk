/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include "pce/hardware.h"
#include <stdint.h>

void pce_irq_enable(uint8_t mask) { *IO_IRQ_CONTROL &= ~mask; }

void pce_irq_disable(uint8_t mask) { *IO_IRQ_CONTROL |= mask; }

void pce_timer_set(uint8_t count) { *IO_TIMER_COUNTER = count; }

void pce_timer_enable(void) { *IO_TIMER_CONTROL = TIMER_ON; }

void pce_timer_disable(void) { *IO_TIMER_CONTROL = TIMER_OFF; }
