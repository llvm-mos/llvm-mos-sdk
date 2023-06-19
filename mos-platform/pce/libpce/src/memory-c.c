/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <stdint.h>
#include <string.h>
#include "pce/hardware.h"
#include "pce/memory.h"

void *memcpy(void *dest, const void *src, size_t count) {
    if (count != 0) return pce_memcpy(dest, src, count);
    else return dest;
}
void *rmemcpy(void *dest, const void *src, size_t count) {
    if (count != 0) return pce_rmemcpy(dest, src, count);
    else return dest;
}
void *memset(void *ptr, int value, size_t num) {
    return pce_memset(ptr, value, num);
}
void __memset(char *ptr, char value, size_t num) {
    pce_memset(ptr, value, num);
}    
void *memmove(void *dest, const void *src, size_t num) {
    if (num != 0) return pce_memmove(dest, src, num);
    else return dest;
}