#include <stdlib.h>
#include <stdio.h>

__attribute__((noreturn)) void _exit(int status);
void _fini();

void exit(int status) {
  _fini();
  _exit(status);
}
