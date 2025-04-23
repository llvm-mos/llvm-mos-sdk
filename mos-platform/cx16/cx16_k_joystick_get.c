#include <cx16.h>

JoyState cx16_k_joystick_get(const unsigned char joystick_num) {
  JoyState s;
  __attribute__((leaf)) asm volatile(
      "jsr __JOYSTICK_GET\n"
      : /* output */ "=a"(s.data0), "=x"(s.data1), "=y"(s.detached)
      : /* input */ "a"(joystick_num)
      : /* clobber */ "p");
  return s;
}
