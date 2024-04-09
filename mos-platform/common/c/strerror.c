#include <string.h>

#include <errno.h>

__attribute__((weak)) const char *strerror(int n) {
#define CASE(NAME)                                                             \
  case NAME:                                                                   \
    return #NAME

  switch (n) {
  CASE(EACCES);
  CASE(EBADF);
  CASE(EBUSY);
  CASE(EDOM);
  CASE(EEXIST);
  CASE(EILSEQ);
  CASE(EINVAL);
  CASE(EIO);
  CASE(ENODEV);
  CASE(ENOENT);
  CASE(ENOMEM);
  CASE(ENOSPC);
  CASE(ENOSYS);
  CASE(EMFILE);
  CASE(ERANGE);
  CASE(ESPIPE);
  default:
    return "unknown";
  }
}
