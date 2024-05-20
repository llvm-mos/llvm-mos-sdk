// Copyright 2022 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Originally from the Public Domain C Library (PDCLib).

struct _FILE;
typedef struct _FILE FILE;

#define BUFSIZ 256
#define EOF (-1)
#define FOPEN_MAX 8

/* See setvbuf(), third argument */
#define _IOFBF (1u << 0)
#define _IOLBF (1u << 1)
#define _IONBF (1u << 2)

typedef uint64_t fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define L_tmpnam 6

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define TMP_MAX 25

// Operations on files
int remove(const char *filename);
int rename(const char *old, const char *_new);
FILE *tmpfile(void);
char *tmpnam(char *s);

// File access functions

int fclose(FILE *stream);
int fflush(FILE *stream);
FILE *fopen(const char *__restrict__ filename, const char *__restrict__ mode);
FILE *freopen(const char *__restrict__ filename, const char *__restrict__ mode,
              FILE *__restrict__ stream);
void setbuf(FILE *__restrict__ stream, char *__restrict__ buf);
int setvbuf(FILE *__restrict__ stream, char *__restrict__ buf, int mode,
            size_t size);

// Formated input/output functions

int fprintf(FILE *__restrict__ stream, const char *__restrict__ format, ...);
int fscanf(FILE *__restrict__ stream, const char *__restrict__ format, ...);
int printf(const char *__restrict__ format, ...);
int scanf(const char *__restrict__ format, ...);
int snprintf(char *__restrict__ s, size_t n, const char *__restrict__ format,
             ...);
int sprintf(char *__restrict__ s, const char *__restrict__ format, ...);
int sscanf(const char *__restrict__ s, const char *__restrict__ format, ...);
int vfprintf(FILE *__restrict__ stream, const char *__restrict__ format,
             va_list arg);
int vfscanf(FILE *__restrict__ stream, const char *__restrict__ format,
            va_list arg);
int vprintf(const char *__restrict__ format, va_list arg);
int vscanf(const char *__restrict__ format, va_list arg);
int vsnprintf(char *__restrict__ s, size_t n, const char *__restrict__ format,
              va_list arg);
int vsprintf(char *__restrict__ s, const char *__restrict__ format,
             va_list arg);
int vsscanf(const char *__restrict__ s, const char *__restrict__ format,
            va_list arg);

// Character input/output functions

int fgetc(FILE *stream);
char *fgets(char *__restrict__ s, int n, FILE *__restrict__ stream);
int fputc(int c, FILE *stream);
int fputs(const char *__restrict__ s, FILE *__restrict__ stream);
int getc(FILE *stream);
int getchar(void);
int putc(int c, FILE *stream);
int putchar(int c);
int puts(const char *s);
int ungetc(int c, FILE *stream);

// Direct input/output functions

size_t fread(void *__restrict ptr, size_t size, size_t nmemb,
             FILE *__restrict__ stream);

size_t fwrite(const void *__restrict ptr, size_t size, size_t nmemb,
              FILE *__restrict__ stream);

// File positioning functions

int fgetpos(FILE *__restrict__ stream, fpos_t *__restrict__ pos);
int fseek(FILE *stream, long int offset, int whence);
int fsetpos(FILE *stream, const fpos_t *pos);
long int ftell(FILE *stream);
void rewind(FILE *stream);

// Error-handling functions

void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *s);

// Platform-specific backend

// Write a sequence of characters in the target's character set that
// correspond to the given ASCII character. Returns EOF on write failure.
__attribute__((always_inline)) int
__from_ascii(char c, void *ctx, int (*write)(char c, void *ctx));

// Read a sequence of characters in the target's character set and return the
// corrsponding ASCII character. Returns EOF on read failure.
__attribute__((always_inline)) int __to_ascii(void *ctx,
                                              int (*read)(void *ctx));

// Put a character in the target's character set out to the target's
// equivalent of file descriptor 1 (stdout).
void __putchar(char c);

// Get a character in the target's character set from to the target's
// equivalent of file descriptor 0 (stdin).
int __getchar(void);

#ifdef __cplusplus
}
#endif

#endif // not _STDIO_H_
