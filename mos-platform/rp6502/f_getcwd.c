#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getcwd(char *name, int size) {
  int i, ax;
  ria_set_ax(size);
  ax = ria_call_int(RIA_OP_GETCWD);
  for (i = 0; i < ax; i++) {
    name[i] = ria_pop_char();
  }
  return ax;
}
