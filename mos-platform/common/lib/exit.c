#include <stdlib.h>
#include <stdio.h>

__attribute__((noreturn)) void __exit(int status);
void _fini();

void exit(int status) {
  _fini();
  __exit(status);
}
