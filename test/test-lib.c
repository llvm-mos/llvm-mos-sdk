#include <peekpoke.h>

__attribute__((noreturn)) void _exit(int status) {
  // This is an unused APU test register, so it should be safe to use writing to
  // this address to report the exit code to the controlling Mesen Lua script.
  POKE(0x4018, status);
  __builtin_unreachable();
}
