#include <sim_io.h>
#include <stdio.h>

volatile struct _sim_reg *const sim_reg_iface =
    ((volatile struct _sim_reg *)0xFFF0);

int getchar() {
  // fetch char (may block)
  const char c = sim_reg_iface->getchar;

  // check eof status of last fetch
  if (sim_reg_iface->input_eof) {
    return EOF;
  }

  return c;
}
