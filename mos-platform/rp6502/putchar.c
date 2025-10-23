#include "rp6502.h"
#include <stdio.h>
#include <unistd.h>

void __putchar(char c) {
  ria_push_char(c);
  ria_set_a(STDOUT_FILENO);
  ria_call_int(RIA_OP_WRITE_XSTACK);
}
