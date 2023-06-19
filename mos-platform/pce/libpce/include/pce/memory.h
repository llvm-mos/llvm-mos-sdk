/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_MEMORY_H_
#define _PCE_MEMORY_H_

#include <stdbool.h>
#include <stdint.h>

/** \file memory.h
 * Functionality related to memory operations.
 */

__attribute__((leaf)) void *pce_memcpy(void *dest, const void *src, uint16_t count);
__attribute__((leaf)) void *pce_rmemcpy(void *dest, const void *src, uint16_t count);
__attribute__((leaf)) void *pce_memset(void *ptr, uint8_t value, uint16_t num);
__attribute__((leaf)) void *pce_memmove(void *dest, const void *src, uint16_t num);

#endif /* _PCE_MEMORY_H_ */
