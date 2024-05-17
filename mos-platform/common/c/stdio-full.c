
// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from the Public Domain C Library (PDCLib)

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  char *filename;       // Name the current stream has been opened with
  FILE *next;           // Pointer to next struct (internal)
};

static FILE serr = {.handle = 2, .status = _IONBF | FWRITE};
static FILE sout = {.handle = 1, .status = _IONBF | FWRITE, .next = &serr};
static FILE sin = {.handle = 0, .status = _IONBF | FREAD, .next = &sout};

FILE *stdin = &sin;
FILE *stdout = &sout;
FILE *stderr = &serr;

static FILE *filelist = &sin;

// This must happen before all POSIX open files are closed.
asm(".section .fini.100,\"axR\",@progbits\n"
    "  jsr _stdio_closeall\n");

void _stdio_closeall(void) {
  for (FILE *f = filelist; f; f = f->next)
    fclose(f);
}

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

// Operations on files

FILE *tmpfile(void) {
  char name[L_tmpnam];
  tmpnam(name);
  FILE *f = fopen(name, "wb+");
  f->status |= DELONCLOSE;
  return f;
}

char *tmpnam(char *s) {
  static char filename[L_tmpnam];
  if (s == NULL)
    s = filename;

  strcpy(s, "tmp00");
  while (s[4] != '2' || s[3] != '4') {
    FILE *f = fopen(s, "rb");
    if (!f)
      break;
    fclose(f);
    if (s[3] == '9') {
      s[3] = '0';
      ++s[4];
    } else {
      ++s[3];
    }
  }

  return s;
}

// File access functions

/* A system call that writes a stream's buffer.
   Returns 0 on success, EOF on write error.
   Sets stream error flags and errno appropriately on error.
*/
static int flush_buffer(FILE *stream) {
  // No need to handle buffers > INT_MAX, as PDCLib doesn't allow them */
  size_t written = 0;
  int rc;

  // Note: everything written to the buffer has already been converted.
  // Otherwise, when write errors occur, it's unclear what still remains to be
  // converted.

  // Keep trying to write data until everything is written or an error occurs.
  for (;;) {
    rc = write(stream->handle, stream->buffer + written,
               stream->bufidx - written);

    if (rc < 0) {
      /* Flag the stream */
      stream->status |= ERRORFLAG;
      /* Move unwritten remains to begin of buffer. */
      stream->bufidx -= written;
      memmove(stream->buffer, stream->buffer + written, stream->bufidx);
      return EOF;
    }

    written += (size_t)rc;
    stream->pos += rc;

    if (written == stream->bufidx) {
      /* Buffer written completely. */
      stream->bufidx = 0;
      return 0;
    }
  }
}

// Removes the given stream from the internal list of open files.
void remove_stream(FILE *stream) {
  for (FILE *f; f; f = f->next) {
    if (f->next == stream) {
      f->next = f->next->next;
      break;
    }
  }
}

int fclose(FILE *stream) {
  /* Flush buffer */
  if (stream->status & FWRITE && flush_buffer(stream) == EOF)
    return EOF;

  /* Close handle */
  close(stream->handle);

  /* Remove stream from list */
  remove_stream(stream);

  /* Delete tmpfile() */
  if (stream->status & DELONCLOSE)
    remove(stream->filename);

  /* Free buffer */
  if (stream->status & FREEBUFFER)
    free(stream->buffer);

  /* Free filename (standard streams do not have one, but free( NULL )
     is a valid no-op)
  */
  free(stream->filename);

  /* Free stream */
  if (stream != stdin && stream != stdout && stream != stderr)
    free(stream);

  return 0;
}

int fflush(FILE *stream) {
  int rc = 0;

  if (stream == NULL) {
    /* TODO: Check what happens when fflush( NULL ) encounters write errors, in
     * other libs */
    for (stream = filelist; stream != NULL; stream = stream->next)
      if (stream->status & FWRITE)
        if (flush_buffer(stream) == EOF)
          rc = EOF;
  } else {
    rc = flush_buffer(stream);
  }

  return rc;
}

FILE *fopen(const char *restrict filename, const char *restrict mode) {
  unsigned int fmode = filemode(mode);

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

  rc->filename = malloc(strlen(filename));
  strcpy(rc->filename, filename);

  rc->next = filelist;
  filelist = rc;

  return rc;
}

// TODO: Support mode changes
static int change_mode(FILE *stream, unsigned int mode) {
  if (mode == 0)
    return INT_MIN;

  /* Attempt mode change without closing the stream */

  if (stream->filename == NULL) {
    /* Standard stream, no filename for reopen */
    return INT_MIN;
  } else {
    /* Stream with file associated, attempt reopen */
    return 0;
  }
}

FILE *freopen(const char *restrict filename, const char *restrict mode,
              FILE *restrict stream) {
  unsigned int fmode = filemode(mode);

  if (stream == NULL) {
    errno = EBADF;
    return NULL;
  }

  /* Flush buffer */
  if (stream->status & FWRITE)
    flush_buffer(stream);

  if (filename == NULL) {
    /* Attempt to change mode without closing stream */
    switch (change_mode(stream, fmode)) {
    case INT_MIN:
      /* fail completely */
      return NULL;

    case 0:
      /* fail; try close / reopen */
      filename = stream->filename;
      /* Setting to NULL to make the free() below a non-op. */
      stream->filename = NULL;
      break;

    default:
      /* success */
      return stream;
    }
  }

  /* Close handle */
  close(stream->handle);

  /* Remove stream from list */
  remove_stream(stream);

  /* Delete tmpfile() */
  if (stream->status & DELONCLOSE) {
    /* Have to switch here; stream->filename may have moved to
       filename after failed in-place mode change above.
    */
    remove((stream->filename == NULL) ? filename : stream->filename);
    stream->status &= ~DELONCLOSE;
  }

  /* Free buffer */
  if (stream->status & FREEBUFFER)
    free(stream->buffer);

  if (filename == NULL) {
    /* Input was filename NULL, stream->filename NULL.
       No filename means there is nothing to reopen. In-place
       mode change was already attempted (and failed) above.
    */
    return NULL;
  } else {
    /* We have a filename, either from input or (if filename
       was NULL) from stream. We will attempt the re-open with
       that, and will retrieve _PDCLIB_realpath() from that.
       So stream->filename is no longer needed.
    */
    free(stream->filename);
  }

  /* Stream is closed, or never was open at this point.
     Now we check if we have the whereabouts to open it.
  */

  if (fmode == 0) {
    /* Mode invalid */
    free(stream->filename);
    free(stream);
    return NULL;
  }

  if (filename == NULL || filename[0] == '\0') {
    /* No filename available (standard stream?) */
    free(stream->filename);
    free(stream);
    return NULL;
  }

  /* (Re-)initializing the structure. */
  if (init_file(stream) == NULL) {
    /* Re-init failed. */
    free(stream->filename);
    free(stream);
    return NULL;
  }

  /* Resetting buffer mode and filemode */
  stream->status |= fmode | _IOLBF;

  /* Attempt open */
  if ((stream->handle = stdio_open(filename, stream->status)) == -1) {
    /* OS open() failed */
    free(stream->filename);
    free(stream->buffer);
    free(stream);
    return NULL;
  }

  stream->filename = malloc(strlen(filename));
  strcpy(stream->filename, filename);

  /* Adding to list of open files */
  stream->next = filelist;
  filelist = stream;

  return stream;
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

static int prepwrite(FILE *stream) {
  if ((stream->bufidx < stream->bufend) || stream->ungetc_buf_full ||
      (stream->status & (FREAD | ERRORFLAG | WIDESTREAM | EOFFLAG)) ||
      !(stream->status & (FWRITE | FAPPEND | FRW))) {
    /* Function called on illegal (e.g. input) stream. */
    errno = EBADF;
    stream->status |= ERRORFLAG;
    return EOF;
  }

  stream->status |= FWRITE | BYTESTREAM;
  return 0;
}

typedef struct {
  FILE *stream;
  bool error;
} WriteCtx;

__attribute((always_inline)) static void write_to_buffer(char c, void *vctx) {
  WriteCtx *ctx = vctx;
  if (ctx->error)
    return;
  ctx->stream->buffer[ctx->stream->bufidx++] = c;
  if (ctx->stream->bufidx == ctx->stream->bufsize &&
      flush_buffer(ctx->stream) == EOF)
    ctx->error = true;
}

size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb,
              FILE *restrict stream) {
  size_t last_newline_idx = 0;
  size_t nmemb_i;

  if (prepwrite(stream) == EOF)
    return 0;

  WriteCtx ctx = {stream};

  for (nmemb_i = 0; nmemb_i < nmemb; ++nmemb_i) {
    for (size_t size_i = 0; size_i < size; ++size_i) {
      char c = ((char *)ptr)[nmemb_i * size + size_i];
      if (stream->status & FBIN)
        write_to_buffer(c, &ctx);
      else
        __from_ascii(c, &ctx, write_to_buffer);
      if (!stream->bufidx)
        last_newline_idx = 0;
      else if (c == '\n')
        last_newline_idx = stream->bufidx;

      if (ctx.error) {
        /* Returning number of objects completely buffered */
        return nmemb_i;
      }
    }
  }

  /* Fully-buffered streams are OK. Non-buffered streams must be flushed,
     line-buffered streams only if there's a newline in the buffer.
  */
  switch (stream->status & (_IONBF | _IOLBF)) {
  case _IONBF:
    if (flush_buffer(stream) == EOF) {
      /* We are in a pinch here. We have an error, which requires a
         return value < nmemb. On the other hand, all objects have
         been written to buffer, which means all the caller had to
         do was removing the error cause, and re-flush the stream...
         Catch 22. We'll return a value one short, to indicate the
         error, and can't really do anything about the inconsistency.
      */
      return nmemb_i - 1;
    }

    break;

  case _IOLBF:
    if (last_newline_idx > 0) {
      size_t bufidx = stream->bufidx;
      stream->bufidx = last_newline_idx;

      if (flush_buffer(stream) == EOF) {
        /* See comment above. */
        stream->bufidx = bufidx;
        return nmemb_i - 1;
      }

      stream->bufidx = bufidx - last_newline_idx;
      memmove(stream->buffer, stream->buffer + last_newline_idx,
              stream->bufidx);
    }
  }

  return nmemb_i;
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
