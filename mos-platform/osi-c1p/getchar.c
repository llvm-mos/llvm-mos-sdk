#include <stdio.h>
#include <stdlib.h>

extern void __kbhit(void);
extern unsigned char volatile __CHARBUF;

int __getchar(void) {
  do {
    __kbhit();
  } while (!__CHARBUF);

  int const result = __CHARBUF;

  __CHARBUF = 0;

  return result;
}
