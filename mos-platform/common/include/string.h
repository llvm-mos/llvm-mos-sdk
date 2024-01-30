
#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Copying functions
void *memcpy(void *__restrict__ s1, const void *__restrict__ s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
char *strcpy(char *__restrict__ s1, const char *__restrict__ s2);
char *strncpy(char *__restrict__ s1, const char *__restrict__ s2, size_t n);

// Concatenation functions

char *strcat(char *__restrict__ s1, const char *__restrict__ s2);
char *strncat(char *__restrict__ s1, const char *__restrict__ s2, size_t n);

// Comparison functions

int memcmp(const void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

// Search functions

void *memchr(const void *s, int c, size_t n);
char *strchr(const char *s, int c);
size_t strcspn(const char *s1, const char *s2);
char *strpbrk(const char *s1, const char *s2);
char *strrchr(const char *s, int c);
size_t strspn(const char *s1, const char *s2);
char *strstr(const char *s1, const char *s2);
char *strtok(char *__restrict__ s1, const char *__restrict__ s2);

// Miscellaneous functions

void *memset(void *ptr, int value, size_t num);
const char *strerror(int n);

size_t strlen(const char *s);

char *_strrev(char *str);

// Version of memset with better arguments for MOS. All non-pointer arguments
// can fit in registers, and there is no superfluous return value. Compiler
// intrinsic memset calls use this version, and user code is free to as well.
void __memset(char *ptr, char value, size_t num);

#ifdef __cplusplus
}
#endif

#endif // not _STRING_H_
