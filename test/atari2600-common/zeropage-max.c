#include <string.h>
#include <mapper.h>
#include <peekpoke.h>

#include "vcslib.h"
#include "test-lib-vcs.h"

// 128 bytes PIA RAM
// 32 bytes for registers
// 32 bytes for stack (overestimate)
// 8 bytes for test result
char buf[128 - 32 - 16 - 8];

void test_zp_max() {
  // set memory
  memset(buf, 0x55, sizeof(buf));
  // compare memory
  for (int i = 0; i < sizeof(buf); i++) {
    if (buf[i] != 0x55) {
      test_failed();
    }
  }
}

int main(void) {
  test_zp_max();
  test_passed();
  return 0;
}
