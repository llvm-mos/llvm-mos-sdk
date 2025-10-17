#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getcwd(char *name, unsigned len) {
  int i, ax;
  ria_set_ax(len);
  ax = ria_call_int(RIA_OP_GETCWD);
  for (i = 0; i < ax; i++) {
    name[i] = ria_pop_char();
  }
  return ax;
}
