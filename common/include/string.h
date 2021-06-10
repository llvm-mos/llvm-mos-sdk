
#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *ptr, int value, size_t num);

char *strchr(const char *s, int c);

int strcmp(const char *s1, const char *s2);

char* strcpy(char *restrict s1, const char *restrict s2);

size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
char *strncpy(char *restrict s1, const char *restrict s2, size_t n);

char *strrchr(const char *s, int c);

// Version of memset with better arguments for MOS. All non-pointer arguments
// can fit in registers, and there is no superfluous return value. Compiler
// intrinsic memset calls use this version, and user code is free to as well.
void __memset(char *ptr, char value, size_t num);

#ifdef __cplusplus
}
#endif

#endif // not _STRING_H_
