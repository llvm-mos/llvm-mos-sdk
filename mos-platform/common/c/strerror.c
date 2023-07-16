#include <string.h>

static const char *errors[] = {"ERANGE", "EDOM", "EILSEQ", "EINVAL", "ENOMEM"};

__attribute__((weak)) const char *strerror(int n) {
  if (n > 0) {
    return errors[((unsigned char)n) - 1];
  } else {
    return "";
  }
}
