// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _KERNEL_H
#define _KERNEL_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Kernel call: Write a character to the current console, inlined.
 *
 * @param c The character to write.
 */
#define KWriteCharacterInline(c) \
	__attribute__((leaf)) asm volatile("jsr 0xFFF5\n.byte %0\n" : : "i"(c) : "p")

/**
 * @brief Kernel call: Read line from the current console.
 *
 * @param s String location.
 */
__attribute__((leaf))
static inline void KReadLine(char *s) {
	uint8_t sl = (uint16_t) s;
	uint8_t sh = ((uint16_t) s) >> 8;
	__attribute__((leaf)) asm volatile("jsr 0xFFEB" : : "x"(sl), "y"(sh) : "p");
}

/**
 * @brief Kernel call: Read a character from the current console.
 *
 * @return char Character.
 */
__attribute__((leaf))
static inline char KReadCharacter(void) {
	char c;
	__attribute__((leaf)) asm volatile("jsr 0xFFEE" : "=a"(c) : : "p");
	return c;
}

/**
 * @brief Kernel call: Write a character to the current console.
 *
 * @param c Character.
 */
__attribute__((leaf))
static inline void KWriteCharacter(char c) {
	__attribute__((leaf)) asm volatile("jsr 0xFFF1" : : "a"(c) : "p");
}

/**
 * @brief Kernel call: Wait for the current command to finish executing.
 */
__attribute__((leaf))
static inline void KWaitMessage(void) {
	__attribute__((leaf)) asm volatile("jsr 0xFFF4" : : : "p");
}

/**
 * @brief Kernel call: Send a command, inlined.
 *
 * @param group The command group.
 * @param function The command function.
 */
#define KSendMessage(group, function) \
	__attribute__((leaf)) asm volatile("jsr 0xFFF7\n.byte %0, %1\n" : : "i"(group), "i"(function) : "p")

/**
 * @brief Combines KSendMessage and KWaitMessage.
 */
#define KSendMessageSync(group, function) \
	KSendMessage(group, function); \
	KWaitMessage()

#ifdef __cplusplus
}
#endif

#endif
