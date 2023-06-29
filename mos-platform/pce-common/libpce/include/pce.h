/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_H_
#define _PCE_H_

#include <pce/hardware.h>

#ifndef __ASSEMBLER__
#include <pce/bank.h>
#include <pce/config.h>
#include <pce/joypad.h>
#include <pce/memory.h>
#include <pce/psg.h>
#include <pce/system.h>
#include <pce/vce.h>
#include <pce/vdc.h>
#endif

#ifdef __PCE_CD__
#include <pce-cd.h>
#endif

#endif /* _PCE_H_ */
