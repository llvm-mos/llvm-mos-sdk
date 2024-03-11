#include <string.h>

#include <errno.h>

static const char *errors[] = {"ERANGE", "EDOM", "EILSEQ", "EINVAL", "ENOMEM"};

__attribute__((weak)) const char *strerror(int n) {
#define CASE(NAME)                                                             \
  case NAME:                                                                   \
    return #NAME

  switch (n) {
    CASE(ERANGE);
    CASE(EDOM);
    CASE(EILSEQ);
    CASE(EINVAL);
    CASE(ENOMEM);
    CASE(ESPIPE);
  default:
    return "unknown";
  }
}
