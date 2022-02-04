#include <stdlib.h>

__attribute__((leaf)) void _fini(void);

void exit(int status) {
  _fini();
  _exit(status);
}
