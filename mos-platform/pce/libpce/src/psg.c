/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include "pce/hardware.h"
#include "pce/memory.h"

__attribute__((alias("pce_psg_reset")))
void __pce_psg_init(void);

void pce_psg_reset(void) {
    *IO_PSG_VOLUME = 0;
	for (uint8_t i = 0; i < 6; i++) {
        *IO_PSG_CH_SELECT = i;
        *IO_PSG_CH_CONTROL = 0;
        *IO_PSG_CH_NOISE = 0;
        *IO_PSG_CH_VOLUME = 0;
    }
}