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

#ifdef __cplusplus
extern "C" {
#endif

/** \file memory.h
 * Functionality related to memory operations.
 */

/**
 * @brief Memory operation mode: Increment source, increment destination.
 */
#define PCE_MEMOP_INCR_INCR 0x73
/**
 * @brief Memory operation mode: Decrement source, decrement destination.
 */
#define PCE_MEMOP_DECR_DECR 0xC3
/**
 * @brief Memory operation mode: Increment source, no change to destination.
 */
#define PCE_MEMOP_INCR_NONE 0xD3
/**
 * @brief Memory operation mode: Increment source, alternate between destination and destination + 1.
 */
#define PCE_MEMOP_INCR_ALT  0xE3
/**
 * @brief Memory operation mode: Alternate between source and source + 1, increment destination.
 */
#define PCE_MEMOP_ALT_INCR  0xF3

/**
 * @brief Perform a memory operation.
 *
 * Note that this function will stall interrupts until it is complete.
 * 
 * @param dest The destination address.
 * @param src The source address.
 * @param count Number of repetitions (bytes). Note that 0 is equivalent to 65,536 bytes.
 * @param mode The memory operation mode.
 */
__attribute__((leaf)) void *pce_memop(void *dest, const void *src, uint16_t count, uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif /* _PCE_MEMORY_H_ */
