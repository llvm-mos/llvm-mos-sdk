// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _ROMPOKE_H_
#define _ROMPOKE_H_

/**
 * @brief Write a value to the ROM bus safely.
 *
 * Explanation:
 *
 * Some NES mappers suffer from bus conflicts, which lead to both
 * the CPU and the ROM driving the data bus at the same time.
 *
 * In order to ensure that a write goes through correctly on such a mapper,
 * the value being written by the CPU must equal the value being read from
 * the ROM at the same address.
 *
 * @param value The value to write.
 */
__attribute__((leaf)) void rom_poke_safe(char value);

#endif /* _ROMPOKE_H_ */
