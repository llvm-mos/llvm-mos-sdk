// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Originally from the Public Domain C Library (PDCLib).

struct _FILE;
typedef struct _FILE FILE;

#define EOF (-1)

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

// Formated input/output functions

int fprintf(FILE *__restrict__ stream, const char *__restrict__ format, ...);
int printf(const char *__restrict__ format, ...);
int snprintf(char *__restrict__ s, size_t n, const char *__restrict__ format,
             ...);
int sprintf(char *__restrict__ s, const char *__restrict__ format, ...);
int vfprintf(FILE *__restrict__ stream, const char *__restrict__ format,
             va_list arg);
int vprintf(const char *__restrict__ format, va_list arg);
int vsnprintf(char *__restrict__ s, size_t n, const char *__restrict__ format,
              va_list arg);
int vsprintf(char *__restrict__ s, const char *__restrict__ format,
             va_list arg);

// Character input/output functions

int fgetc(FILE *stream);
char *fgets(char *__restrict__ s, int n, FILE *__restrict__ stream);
int fputc(int c, FILE *stream);
int fputs(const char *__restrict__ s, FILE *__restrict__ stream);
int getc(FILE *stream);
int getchar(void);
int putchar(int c);
int puts(const char *s);

// Error-handling functions

int feof(FILE *stream);
int ferror(FILE *stream);

// Platform-specific backend

// Emit a sequence of characters in the target's character set that
// correspond to the given ASCII character.
__attribute__((always_inline)) void __from_ascii(char c, void (*emit)(char c));

// Put a character already in the target's character set out to the target's
// equivalent of file descriptor 0.
void __putchar(char c);

#ifdef __cplusplus
}
#endif

#endif // not _STDIO_H_
