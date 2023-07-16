/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _RPC8E_CPU_H_
#define _RPC8E_CPU_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file cpu.h
 * Functionality related to the CPU.
 */

/**
 * @brief Emit a WAI instruction, causing the CPU to wait.
 *
 * On 65EL02, this means stalling for 1 world tick (0.05 seconds).
 */
static inline void rpc8e_cpu_wait(void) {
  __attribute__((leaf)) asm volatile("wai");
}

#ifdef __cplusplus
}
#endif

#endif /* _RPC8E_CPU_H_ */
