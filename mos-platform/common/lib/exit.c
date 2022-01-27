#include <stdlib.h>

void _fini(void);

void exit(int status) {
  _fini();
  _exit(status);
}
