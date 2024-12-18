#include <string.h>
#include <mapper.h>
#include <peekpoke.h>

#include "vcslib.h"
#include "test-lib-vcs.h"

// 128 bytes PIA RAM
// 32 bytes for registers
// 16 bytes for stack
// 8 bytes for test result
char buf[128 - 32 - 16 - 8];

void test_recurse(int n) {
  if (n == 0) {
    return;
  }
  buf[0]++;
  test_recurse(n - 1);
  buf[0]--;
}

void test_zp_max() {
  // set memory
  memset(buf, 0x55, sizeof(buf));
  // test 10 layers of recursion
  test_recurse(10);
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
