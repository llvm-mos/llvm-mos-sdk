#include "rp6502.h"
#include <stdio.h>
#include <unistd.h>

int __getchar(void) {
  ria_push_char(1);
  ria_set_a(STDIN_FILENO);
  if (ria_call_int(RIA_OP_READ_XSTACK) == 1)
    return RIA.xstack;
  return EOF;
}
