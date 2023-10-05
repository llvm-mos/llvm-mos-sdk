#include <peekpoke.h>

__attribute__((weak)) void __putchar(char c) {
  // To be picked up by an emulator debug script to redirect the output to host
  // standard out. 0x401B is unused, so writing there can be unambiguously
  // interpreted as an attempt to write to stdout (in the absence of another use
  // by the user, in which case this function is left weak so it can be
  // overriden.
  POKE(0x401B, c);
}
