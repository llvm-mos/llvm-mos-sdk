// Shared xemu test utilities for MEGA65 tests.
// Uses the xemu $D6CF control register to signal test exit codes.

#ifndef XEMU_TEST_H
#define XEMU_TEST_H

#include <mega65.h>
#include <stdint.h>

#define XEMU_CONTROL (*(volatile uint8_t *)0xd6cf)
#define XEMU_QUIT 0x42

static __attribute__((noinline, noreturn)) void xemu_exit(uint8_t code) {
  // MAP outranks $01/$D030 banking, so a MAP block covering $C000-$DFFF
  // hides I/O, and $D6CF with it. Clear MAP so $D000-$DFFF falls through
  // to I/O routing whatever the caller left mapped.
  asm volatile("lda #$00\n\t"
               "tax\n\t"
               "tay\n\t"
               "taz\n\t"
               "map\n\t"
               "eom\n\t"
               "sei" ::
                   : "a", "x", "y", "p");
  // One pair suffices whatever came before: each write stores its byte as the
  // new key, so the first sets up the second.
  VICIV.key = VIC4_KEY_VICIV_A;
  VICIV.key = VIC4_KEY_VICIV_B;
  XEMU_CONTROL = code;
  XEMU_CONTROL = XEMU_QUIT;
  // Wait for the emulator to go. An empty loop would be undefined behaviour
  // and may be deleted, letting control run off the end of this function.
  for (;;)
    asm volatile("");
}

// Assert condition; on failure exits with source line number as exit code.
// Exit codes are one byte, so a line past 255 is clamped rather than wrapped:
// wrapping line 256 would report 0, which is the code for success.
#define xemu_assert(cond)                                                      \
  do {                                                                         \
    if (!(cond))                                                               \
      xemu_exit(__LINE__ > 255 ? 255 : (uint8_t)__LINE__);                     \
  } while (0)

#endif // XEMU_TEST_H
