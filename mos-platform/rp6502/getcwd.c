#include <errno.h>
#include <rp6502.h>
#include <unistd.h>

char *getcwd(char *buf, size_t size) {
  if (f_getcwd(buf, size) < 0) {
    if (errno == ENOMEM)
      errno = ERANGE;
    return 0;
  }
  return buf;
}
