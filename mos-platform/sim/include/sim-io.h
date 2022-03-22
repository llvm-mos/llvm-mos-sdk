#ifndef _SIM_IO_H_
#define _SIM_IO_H_

#include <stdint.h>

struct _sim_reg {
  uint8_t clock[4];     // 0
  uint8_t unclaimed;    // 4
  char getchar;         // 5
  char input_eof;       // 6
  uint8_t abort;        // 7
  int8_t exit;          // 8
  uint8_t putchar;      // 9
};

extern volatile struct _sim_reg *const sim_reg_iface;

#endif // _SIM_IO_H_
