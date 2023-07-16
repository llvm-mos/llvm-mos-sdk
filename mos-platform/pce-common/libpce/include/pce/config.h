/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_CONFIG_H_
#define _PCE_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file config.h
 * Functionality related to output ELF configuration.
 */

#define __PCE_ROM_BANK_DECLARE(id, offset, size)                               \
  asm(".global __rom_bank" #id "\n.global __rom_bank" #id                      \
      "_size\n.equ __rom_bank" #id ", ((" #offset                              \
      ") << 13)\n.equ __rom_bank" #id "_size, ((" #size ") << 13)\n")

#define __PCE_ROM_BANK_USE(id, offset)                                         \
  static inline void pce_rom_bank##id##_map(void) {                            \
    __attribute__((leaf)) asm volatile("lda #mos8(__rom_bank" #id "_bank)\n"   \
                                       "tam #(1 << " #offset ")\n"             \
                                       :                                       \
                                       :                                       \
                                       : "a", "p");                            \
  }

#define __PCE_ROM_BANK_CALLBACK_DECLARE(id, offset)                            \
  __attribute__((                                                              \
      leaf, callback(1), noinline,                                             \
      section("text.pce_rom_bank" #id                                          \
              "_call"))) void pce_rom_bank##id##_call(void (*method)(void)) {  \
    pce_bank##offset##_size1_push();                                           \
    pce_rom_bank##id##_map();                                                  \
    method();                                                                  \
    pce_bank##offset##_size1_pop();                                            \
  }

#define __PCE_ROM_BANK_CALLBACK_USE(id)                                        \
  __attribute__((leaf, callback(1))) void pce_rom_bank##id##_call(             \
      void (*method)(void))

#ifdef PCE_CONFIG_IMPLEMENTATION
#define PCE_ROM_BANK_AT(id, offset)                                            \
  __PCE_ROM_BANK_DECLARE(id, offset, 1);                                       \
  __PCE_ROM_BANK_USE(id, offset)                                               \
  __PCE_ROM_BANK_CALLBACK_DECLARE(id, offset)
#define PCE_ROM_FIXED_BANK_SIZE(size) __PCE_ROM_BANK_DECLARE(0, 8 - size, size)
#define PCE_SGX_RAM(size)                                                      \
  asm(".global __ram_bank_size\n.equ __ram_bank_size, ((" #size ") << 13)\n")
#else
/**
 * @brief Define the memory offset for a given physical bank.
 *
 * A virtual bank is a group of one or more physical banks, automatically
 * allocated by the linker.
 *
 * The recommended way to define virtual banks is to create a header file
 * (for example, "bank.h") with PCE_ROM_BANK_AT entries, and a source
 * file ("bank.c") which defines PCE_CONFIG_IMPLEMENTATION, then
 * includes <pce.h>, then includes "bank.h".
 *
 * A bank N defined in this manner provides:
 * - the pce_rom_bankN_map() function, mapping the requested virtual bank,
 * - the pce_rom_bankN_call(void (*method)(void)) function defines a safe
 *   trampoline to a function in another bank,
 * - the __rom_bankN section.
 *
 * @param id The ID of the physical bank (0-127).
 * @param offset The memory offset, in 8KB units (2-6).
 */
#define PCE_ROM_BANK_AT(id, offset)                                            \
  __PCE_ROM_BANK_USE(id, offset)                                               \
  __PCE_ROM_BANK_CALLBACK_USE(id)
/**
 * @brief Define the size of the fixed bank (at the top of memory).
 *
 * @param size The size, in 8KB units (1-6).
 */
#define PCE_ROM_FIXED_BANK_SIZE(size)
/**
 * @brief Define the amount of C RAM for SGX targets.
 *
 * The SGX provides up to 32 kilobytes of RAM in four banks (0xF8-0xFB),
 * but only one is mapped by default (at offset 0x2000), to preserve
 * compatibility with the standard PCE. Use this define in a source file
 * to map more RAM to C by default.
 *
 * Note that using this will reserve more banks for C RAM and the soft
 * stack; for example, PCE_SGX_RAM(2) will use bank offsets 1 *and* 2.
 *
 * @param size The size, in 8KB units (2-4).
 */
#define PCE_SGX_RAM(size)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PCE_CONFIG_H_ */
