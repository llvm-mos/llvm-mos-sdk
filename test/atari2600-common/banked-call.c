#include <string.h>
#include <mapper.h>
#include <peekpoke.h>

#include "test-lib-vcs.h"

char callmask = 0;

CODE_BANK(1) void banked_call_1() {
  callmask |= 4;
}

CODE_BANK(0) void banked_call_0() {
  callmask |= 1;
  banked_call_rom(1, banked_call_1);
  callmask |= 2;
}

int main(void) {
  banked_call_rom(0, banked_call_0);
  if (callmask != 0b111) test_failed();
  test_passed();
  return 0;
}
