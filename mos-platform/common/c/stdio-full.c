
// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from the Public Domain C Library (PDCLib)

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Flags for representing mode (see fopen()). Note these must fit the same
// status field as the _IO?BF flags in <stdio.h> and the internal flags below.
#define FREAD (1u << 3)
#define FWRITE (1u << 4)
#define FAPPEND (1u << 5)
#define FEXCL (1u << 6)
#define FRW (1u << 7)
#define FBIN (1u << 8)

// Internal flags, made to fit the same status field as the flags above.
// --------------------------------------------------------------------------
// free() the buffer memory on closing (setvbuf()).
#define FREEBUFFER (1u << 9)
// Stream has encountered error / EOF.
#define ERRORFLAG (1u << 10)
#define EOFFLAG (1u << 11)
// Stream is wide-oriented.
#define WIDESTREAM (1u << 12)
// Stream is byte-oriented.
#define BYTESTREAM (1u << 13)
// File associated with stream should be remove()d on closing (tmpfile()).
#define DELONCLOSE (1u << 14)

struct _FILE {
  signed char handle;   // OS file handle
  char *buffer;         // Pointer to buffer memory
  size_t bufsize;       // Size of buffer
  size_t bufidx;        // Index of current position in buffer
  size_t bufend;        // Index of last pre-read character in buffer
  fpos_t pos;           // Offset and multibyte parsing state
  char ungetc_buf;      // ungetc() buffer
  bool ungetc_buf_full; // Number of ungetc()'ed characters
  unsigned status;      // Status flags; see above
};

// Helper function that parses the C-style mode string passed to fopen() into
// the PDCLib flags FREAD, FWRITE, FAPPEND, FRW (read-write) and FBIN (binary
// mode).
static unsigned filemode(const char *const mode) {
  unsigned rc = 0;

  switch (mode[0]) {
  case 'r':
    rc |= FREAD;
    break;

  case 'w':
    rc |= FWRITE;
    break;

  case 'a':
    rc |= FAPPEND | FWRITE;
    break;
  }

  for (int i = 1; i < 4; ++i) {
    switch (mode[i]) {
    case '+':
      rc |= FRW;
      break;

    case 'b':
      rc |= FBIN;
      break;

    case 'x':
      rc |= FEXCL;
      break;

    case '\0':
      // End of mode
      return rc;
    }
  }

  return rc;
}

static FILE *init_file(FILE *stream) {
  FILE *rc = stream;

  if (rc == NULL) {
    if ((rc = (FILE *)malloc(sizeof(struct _FILE))) == NULL) {
      /* No memory */
      return NULL;
    }
  }

  if ((rc->buffer = (char *)malloc(BUFSIZ)) == NULL) {
    /* No memory */
    free(rc);
    return NULL;
  }

  rc->bufsize = BUFSIZ;
  rc->bufidx = 0;
  rc->bufend = 0;
  rc->pos = 0;
  rc->ungetc_buf_full = false;
  rc->status = FREEBUFFER;

  // TODO: Setting mbstate

  return rc;
}

static signed char stdio_open(const char *const filename, unsigned int mode) {
  int osmode;

  if (mode & FRW)
    osmode = O_RDWR;
  else if (mode & FREAD)
    osmode = O_RDONLY;
  else
    osmode = O_WRONLY;

  if (mode & (FWRITE | FAPPEND))
    osmode |= O_CREAT;

  if (mode & FWRITE)
    osmode |= mode & FEXCL ? O_EXCL : O_TRUNC;
  else if (mode & FAPPEND)
    osmode |= O_APPEND;

  return open(filename, osmode);
}

// File access functions

FILE *fopen(const char *restrict filename, const char *restrict mode) {
  unsigned int fmode = filemode(mode);

  // See tmpfile(), which does much of the same.

  // Initializing FILE structure failed.
  FILE *rc;
  if ((rc = init_file(NULL)) == NULL)
    return NULL;

  // Setting buffer to _IOLBF because "when opened, a stream is fully
  // buffered if and only if it can be determined not to refer to an
  // interactive device."
  rc->status |= fmode | _IOLBF;

  if ((rc->handle = stdio_open(filename, rc->status)) == -1)
    return NULL;

  return rc;
}

// Character input/output functions

// Produce a link error if these are used.
__attribute__((noreturn)) void __stdio_not_yet_implemented(void);

int fgetc(FILE *stream) { __stdio_not_yet_implemented(); }

char *fgets(char *__restrict__ s, int n, FILE *__restrict__ stream) {
  __stdio_not_yet_implemented();
}

int fputc(int c, FILE *stream) { __stdio_not_yet_implemented(); }

int fputs(const char *__restrict__ s, FILE *__restrict__ stream) {
  __stdio_not_yet_implemented();
}

int getc(FILE *stream) { __stdio_not_yet_implemented(); }

int getchar(void) { __stdio_not_yet_implemented(); }

int putc(int c, FILE *stream) { __stdio_not_yet_implemented(); }

int putchar(int c) { __stdio_not_yet_implemented(); }

int puts(const char *s) { __stdio_not_yet_implemented(); }

// Direct input/output functions

size_t fread(void *__restrict ptr, size_t size, size_t nmemb,
             FILE *__restrict__ stream) {
  __stdio_not_yet_implemented();
}

size_t fwrite(const void *__restrict ptr, size_t size, size_t nmemb,
              FILE *__restrict__ stream) {
  __stdio_not_yet_implemented();
}

// File positioning functions

int fgetpos(FILE *__restrict__ stream, fpos_t *__restrict__ pos) {
  __stdio_not_yet_implemented();
}

int fseek(FILE *stream, long int offset, int whence) {
  __stdio_not_yet_implemented();
}

int fsetpos(FILE *stream, const fpos_t *pos) { __stdio_not_yet_implemented(); }

long int ftell(FILE *stream) { __stdio_not_yet_implemented(); }

void rewind(FILE *stream) { __stdio_not_yet_implemented(); }

// Error-handling functions

void clearerr(FILE *stream) { __stdio_not_yet_implemented(); }

int feof(FILE *stream) { __stdio_not_yet_implemented(); }

int ferror(FILE *stream) { __stdio_not_yet_implemented(); }

void perror(const char *s) { __stdio_not_yet_implemented(); }
