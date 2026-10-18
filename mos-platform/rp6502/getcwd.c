#include <errno.h>
#include <rp6502.h>
#include <unistd.h>

char *getcwd(char *buf, size_t size) {
  int i, ax;
  if (!size) {
    errno = EINVAL;
    return 0;
  }
  RIA.op = RIA_OP_GETCWD;
  ax = ria_spin();
  if (ax < 0)
    return 0;
  if ((size_t)ax > size) {
    ria_drop();
    errno = ERANGE;
    return 0;
  }
  for (i = 0; i < ax; i++)
    buf[i] = RIA.xstack;
  return buf;
}
