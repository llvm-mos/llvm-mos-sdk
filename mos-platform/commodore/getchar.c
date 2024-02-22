#define __CBM__
#include <cbm.h>
#include <stdint.h>
#include <stdio.h>

// Kernal line buffer is 80 bytes. It appears that if 80 chars are input, the
// buffer is reset.
static char input_buffer[80];
static uint8_t buf_begin;
static uint8_t buf_end;

// Default input from the keyboard device has 80 char edit buffer.
// When you call CHRIN, it waits for the user to input something and does not
// return until RETURN is pressed.  When return is pressed, the contents of the
// line the user entered is available. When CHRIN returns, it appears you
// must keep fetch the rest of the kernal line buffer by repeatedly
// calling CHRIN until you retrieve the carraige return.  Based on examples
// I found online, and through my own testing, it's not safe to do other I/O
// until the input is fully retrieved-- for example calling CHROUT after
// fetching the first buffered character seems to cause the rest of the input
// buffer to drop.  Thus, the entire line is held in our own input buffer.
// Theoretically this maps neatly to the buffer required for the stdin stream.

static void __fill_buffer() {
  // Precondition: the input buffer is empty.
  // Call the CHRIN routine until in returns a CR.
  // The first time through the loop, CHRIN may block while waiting for the
  // user to finish entering data.
  buf_begin = 0;
  buf_end = 0;

  for (;;) {
    const char c = cbm_k_chrin();

    input_buffer[buf_end++] = c;
    if (c == '\r') {
      // Echo carriage return.
      __putchar(c);
      break;
    }
  }
}

int __getchar() {
  if (buf_begin == buf_end)
    __fill_buffer();
  return input_buffer[buf_begin++];
}
