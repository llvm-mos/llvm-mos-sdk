#ifndef __STDIO_INTERNAL_H_
#define __STDIO_INTERNAL_H_

#include <stdbool.h>
#include <stdio.h>

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
  fpos_t diskpos;       // Atari NOTE position
  FILE *next;           // Pointer to next struct (internal)
};

void __update_diskpos(FILE *stream);

#endif // __STDIO_INTERNAL_H_
