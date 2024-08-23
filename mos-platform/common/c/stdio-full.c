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
  char *del_filename;   // Name of the file to be remove()d on closing
  FILE *next;           // Pointer to next struct (internal)
};

// Buffer one-two lines; write() implementations have constant overhead, and
// buffering amortizes it.
static char serr_buf[80];
static char sout_buf[80];
static char sin_buf[80];

static FILE serr = {.handle = 2,
                    .buffer = serr_buf,
                    .bufsize = sizeof(serr_buf),
                    .status = _IONBF | FWRITE};
static FILE sout = {.handle = 1,
                    .buffer = sout_buf,
                    .bufsize = sizeof(sout_buf),
                    .status = _IOLBF | FWRITE,
                    .next = &serr};
static FILE sin = {.handle = 0,
                   .buffer = sin_buf,
                   .bufsize = sizeof(sin_buf),
                   .status = _IOLBF | FREAD,
                   .next = &sout};

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

static int stdio_close(FILE *stream) {
  int rc = 0;

  /* Flush buffer */
  if (stream->status & FWRITE)
    rc = flush_buffer(stream);

  /* Close handle */
  if (close(stream->handle) != 0)
    rc = EOF;

  /* Delete tmpfile() */
  if (stream->del_filename) {
    if (remove(stream->del_filename) != 0)
      rc = EOF;
    free(stream->del_filename);
  }
  return rc;
}

static void free_stream(FILE *stream) {
  /* Remove stream from list */
  if (filelist == stream) {
    filelist = stream->next;
  } else {
    for (FILE *f = filelist;; f = f->next) {
      if (f->next == stream) {
        f->next = f->next->next;
        break;
      }
    }
  }

  /* Free buffer */
  if (stream->status & FREEBUFFER)
    free(stream->buffer);

  /* Free stream */
  if (stream != stdin && stream != stdout && stream != stderr)
    free(stream);
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

// Initializes stream by opening the handle and initializing most of structure
// members.  stream->buffer, stream->bufsize and stream->next must be
// initialized on entry.
// Returns stream on success, NULL on failure (and frees stream).
static FILE *stdio_open(FILE *stream, const char *filename, unsigned int mode) {
  // Setting buffer to _IOLBF because "when opened, a stream is fully
  // buffered if and only if it can be determined not to refer to an
  // interactive device."
  stream->status = mode | _IOLBF | FREEBUFFER;

  int osmode;

  if (mode & FRW)
    osmode = O_RDWR;
  else if (mode & FREAD)
    osmode = O_RDONLY;
  else
    osmode = O_WRONLY;

  if (mode & (FWRITE | FAPPEND))
    osmode |= O_CREAT;    // file doesn't exist: create

  if (mode & FAPPEND) {
    osmode |= O_APPEND;   // file exists: append
  } else if (mode & FWRITE) {
    osmode |= mode & FEXCL
               ? O_EXCL   // file exists: fail
               : O_TRUNC; // file exists: truncate
  }

  stream->handle = open(filename, osmode);
  if (stream->handle == -1) {
    free_stream(stream);
    return NULL;
  }

  stream->bufidx = 0;
  stream->bufend = 0;
  stream->pos = 0;
  stream->ungetc_buf_full = false;
  stream->del_filename = NULL;
  return stream;
}

// Operations on files

FILE *tmpfile(void) {
  char filename[L_tmpnam];
  tmpnam(filename);
  FILE *stream = fopen(filename, "wb+");
  if (stream) {
    stream->del_filename = malloc(strlen(filename));
    if (stream->del_filename)
      strcpy(stream->del_filename, filename);
  }
  return stream;
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

int fclose(FILE *stream) {
  int rc = stdio_close(stream);
  free_stream(stream);
  return rc;
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

  FILE *stream = (FILE *)malloc(sizeof(struct _FILE));
  if (stream == NULL)
    return NULL;

  stream->buffer = (char *)malloc(BUFSIZ);
  if (stream->buffer == NULL) {
    free(stream);
    return NULL;
  }
  stream->bufsize = BUFSIZ;

  stream->next = filelist;
  filelist = stream;
  return stdio_open(stream, filename, fmode);
}

FILE *freopen(const char *restrict filename, const char *restrict mode,
              FILE *restrict stream) {
  unsigned int fmode = filemode(mode);

  if (stream == NULL) {
    errno = EBADF;
    return NULL;
  }

  /* C standard: "Failure to close the file is ignored" */
  stdio_close(stream);

  if (filename == NULL || fmode == 0) {
    free_stream(stream);
    return NULL;
  }

  if (setvbuf(stream, NULL, _IOLBF, BUFSIZ) != 0) {
    free_stream(stream);
    return NULL;
  }

  return stdio_open(stream, filename, fmode);
}

void setbuf(FILE *restrict stream, char *restrict buf) {
  setvbuf(stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}

int setvbuf(FILE *restrict stream, char *restrict buf, int mode, size_t size) {
  switch (mode) {
  case _IONBF:
    /* When unbuffered I/O is requested, we keep the buffer anyway, as
       we don't want to e.g. flush the stream for every character of a
       stream being printed.
    */
    break;

  case _IOFBF:
  case _IOLBF:
    if (size > INT_MAX || size == 0) {
      /* PDCLib only supports buffers up to INT_MAX in size. A size
         of zero doesn't make sense.
      */
      return -1;
    }

    if (buf != NULL) {
      /* User provided buffer. Deallocate existing buffer, and mark
         the stream so that fclose() does not try to deallocate the
         user's buffer.
      */
      if (stream->status & FREEBUFFER)
        free(stream->buffer);

      stream->status &= ~FREEBUFFER;
    } else {
      /* User requested buffer size, but leaves it to library to
         allocate the buffer.
      */
      /* If current buffer is big enough for requested size, but not
         over twice as big (and wasting memory space), we use the
         current buffer (i.e., do nothing), to save the malloc() /
         free() overhead.
      */

      if ((stream->bufsize < size) || (stream->bufsize > (size << 1))) {
        /* Buffer too small, or much too large - allocate. */
        if ((buf = (char *)malloc(size)) == NULL) {
          /* Out of memory error. */
          return -1;
        }

        if (stream->status & FREEBUFFER)
          free(stream->buffer);

        /* This buffer must be free()d on fclose() */
        stream->status |= FREEBUFFER;
      }
    }

    stream->buffer = buf;
    stream->bufsize = size;
    break;

  default:
    /* If mode is something else than _IOFBF, _IOLBF or _IONBF -> exit */
    return -1;
  }

  /* Deleting current buffer mode */
  stream->status &= ~(_IOFBF | _IOLBF | _IONBF);
  /* Set user-defined mode */
  stream->status |= mode;
  return 0;
}

// Character input/output functions

// Produce a link error if these are used.
__attribute__((noreturn)) void __stdio_not_yet_implemented(void);

static int prep_read(FILE *stream) {
  if ((stream->bufidx > stream->bufend) ||
      (stream->status &
       (FWRITE | FAPPEND | ERRORFLAG | WIDESTREAM | EOFFLAG)) ||
      !(stream->status & (FREAD | FRW))) {
    /* Function called on illegal (e.g. output) stream. */
    errno = EBADF;
    stream->status |= ERRORFLAG;
    return EOF;
  }

  stream->status |= FREAD | BYTESTREAM;

  return 0;
}

static int fill_buffer(FILE *stream) {
  /* No need to handle buffers > INT_MAX, as PDCLib doesn't allow them */
  int rc = read(stream->handle, stream->buffer, stream->bufsize);

  if (rc > 0) {
    /* Reading successful. */
    stream->pos += rc;
    stream->bufend = rc;
    stream->bufidx = 0;
    return 0;
  }

  if (rc < 0) {
    /* Flag the stream */
    stream->status |= ERRORFLAG;
    return EOF;
  }

  /* End-of-File */
  stream->status |= EOFFLAG;
  return EOF;
}

__attribute__((always_inline)) static int read_byte(void *ctx) {
  FILE *stream = ctx;
  if (stream->bufidx == stream->bufend)
    if (fill_buffer(stream) == EOF)
      return EOF;
  return stream->buffer[stream->bufidx++];
}

static int read_char(FILE *stream) {
  if (stream->ungetc_buf_full) {
    stream->ungetc_buf_full = false;
    return stream->ungetc_buf;
  }
  return stream->status & FBIN ? read_byte(stream)
                               : __to_ascii(stream, read_byte);
}

int fgetc(FILE *stream) {
  if (prep_read(stream) == EOF)
    return EOF;
  return read_char(stream);
}

char *fgets(char *restrict s, int size, FILE *restrict stream) {
  char *dest = s;
  if (size == 0)
    return NULL;
  if (prep_read(stream) == EOF)
    return NULL;

  for (; size > 1; --size) {
    int c = read_char(stream);
    if (c == EOF) {
      // Don't append '\0' if no characters have been read; just return NULL.
      if (dest == s)
        return NULL;
      else
        break;
    }
    *dest++ = (char)c;
    if (c == '\n')
      break;
  }

  if (ferror(stream))
    return NULL;
  *dest = '\0';
  return s;
}

static int prep_write(FILE *stream) {
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

__attribute__((always_inline)) static int write_byte(char c, void *ctx) {
  FILE *stream = ctx;
  stream->buffer[stream->bufidx++] = c;
  if (stream->bufidx == stream->bufsize)
    if (flush_buffer(stream) == EOF)
      return EOF;
  return 0;
}

static int write_char(char c, FILE *stream) {
  if (stream->status & FBIN) {
    if (write_byte(c, stream) == EOF)
      return EOF;
  } else if (__from_ascii(c, stream, write_byte) == EOF) {
    return EOF;
  }
  if ((stream->status & _IOLBF) && c == '\n')
    if (flush_buffer(stream) == EOF)
      return EOF;
  return 0;
}

int fputc(int c, FILE *stream) {
  if (prep_write(stream) == EOF)
    return EOF;
  if (write_char(c, stream) == EOF)
    return EOF;
  if (stream->status & _IONBF)
    if (flush_buffer(stream) == EOF)
      return EOF;
  return c;
}

int fputs(const char *restrict s, FILE *restrict stream) {
  if (prep_write(stream) == EOF)
    return EOF;
  for (; *s; ++s)
    if (write_char(*s, stream) == EOF)
      return EOF;
  if (stream->status & _IONBF)
    if (flush_buffer(stream) == EOF)
      return EOF;
  return 0;
}

int getchar(void) { return getc(stdin); }

int putchar(int c) { return putc(c, stdout); }

int puts(const char *s) {
  if (prep_write(stdout) == EOF)
    return EOF;
  for (; *s; ++s)
    if (write_char(*s, stdout) == EOF)
      return EOF;
  if (write_char('\n', stdout) == EOF)
    return EOF;
  if (stdout->status & _IONBF)
    return flush_buffer(stdout);
  return 0;
}

int ungetc(int c, FILE *stream) {
  if (c == EOF || stream->ungetc_buf_full)
    return -1;
  stream->ungetc_buf = (char)c;
  stream->ungetc_buf_full = true;
  return c;
}

// Direct input/output functions

size_t fread(void *restrict ptr, size_t size, size_t nmemb,
             FILE *restrict stream) {
  char *dest = (char *)ptr;
  if (prep_read(stream) == EOF)
    return 0;
  size_t nmemb_i;
  for (nmemb_i = 0; nmemb_i < nmemb; ++nmemb_i) {
    /* TODO: For better performance, move from stream buffer
       to destination block-wise, not byte-wise.
    */
    for (size_t size_i = 0; size_i < size; ++size_i) {
      int c = read_char(stream);
      if (c == EOF)
        return nmemb_i;
      dest[nmemb_i * size + size_i] = (char)c;
    }
  }
  return nmemb_i;
}

size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb,
              FILE *restrict stream) {
  size_t nmemb_i;

  if (prep_write(stream) == EOF)
    return 0;

  for (nmemb_i = 0; nmemb_i < nmemb; ++nmemb_i) {
    for (size_t size_i = 0; size_i < size; ++size_i) {
      char c = ((char *)ptr)[nmemb_i * size + size_i];
      if (write_char(c, stream) == EOF)
        return nmemb_i;
    }
  }

  if (stream->status & _IONBF) {
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
  }
  return nmemb_i;
}

// File positioning functions

int fgetpos(FILE *restrict stream, fpos_t *restrict pos) {
  *pos = (stream->pos - (((int)stream->bufend - (int)stream->bufidx) +
                         (int)stream->ungetc_buf_full));
  return 0;
}

static long seek(FILE *stream, long offset, int whence) {
  long rc;

  switch (whence) {
  case SEEK_SET:
  case SEEK_CUR:
  case SEEK_END:
    /* EMPTY - OK */
    break;

  default:
    errno = EINVAL;
    return EOF;
    break;
  }

  rc = lseek(stream->handle, offset, whence);

  if (rc != EOF) {
    stream->ungetc_buf_full = false;
    stream->bufidx = 0;
    stream->bufend = 0;
    stream->pos = rc;
    return rc;
  }

  return EOF;
}

int fseek(FILE *stream, long offset, int whence) {
  int rc;

  if (stream->status & FWRITE)
    if (flush_buffer(stream) == EOF)
      return EOF;

  stream->status &= ~EOFFLAG;

  if (stream->status & FRW)
    stream->status &= ~(FREAD | FWRITE);

  if (whence == SEEK_CUR)
    offset -= (((int)stream->bufend - (int)stream->bufidx) +
               (int)stream->ungetc_buf_full);

  if (seek(stream, offset, whence) == EOF)
    return EOF;
  return 0;
}

int fsetpos(FILE *stream, const fpos_t *pos) {
  if (stream->status & FWRITE)
    if (flush_buffer(stream) == EOF)
      return EOF;
  if (seek(stream, *pos, SEEK_SET) == EOF)
    return EOF;
  return 0;
}

long int ftell(FILE *stream) {
  /* ftell() must take into account:
     - the actual *physical* offset of the file, i.e. the offset as recognized
       by the operating system (and stored in stream->pos.offset); and
     - any buffers held by PDCLib, which
       - in case of unwritten buffers, count in *addition* to the offset; or
       - in case of unprocessed pre-read buffers, count in *substraction* to
         the offset. (Remember to count ungetidx into this number.)
     Conveniently, the calculation ( ( bufend - bufidx ) + ungetidx ) results
     in just the right number in both cases:
       - in case of unwritten buffers, ( ( 0 - unwritten ) + 0 )
         i.e. unwritten bytes as negative number
       - in case of unprocessed pre-read, ( ( preread - processed ) + unget )
         i.e. unprocessed bytes as positive number.
     That is how the somewhat obscure return-value calculation works.
  */
  /*  If offset is too large for return type, report error instead of wrong
      offset value.
  */
  long int rc;
  if ((stream->pos - stream->bufend) >
      (LONG_MAX - (stream->bufidx - (int)stream->ungetc_buf_full))) {
    /* integer overflow */
    errno = ERANGE;
    return -1;
  }
  return (stream->pos - (((int)stream->bufend - (int)stream->bufidx) +
                         (int)stream->ungetc_buf_full));
}

void rewind(FILE *stream) {
  stream->status &= ~ERRORFLAG;
  fseek(stream, 0L, SEEK_SET);
}

// Error-handling functions

void clearerr(FILE *stream) { stream->status &= ~(ERRORFLAG | EOFFLAG); }

int feof(FILE *stream) { return stream->status & EOFFLAG; }

int ferror(FILE *stream) { return stream->status & ERRORFLAG; }
