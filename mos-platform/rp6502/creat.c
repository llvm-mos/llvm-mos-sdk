#include <fcntl.h>

int creat(const char *name, unsigned mode) {
  return open(name, O_WRONLY | O_CREAT | O_TRUNC);
}
