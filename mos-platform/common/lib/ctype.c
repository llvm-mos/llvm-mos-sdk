#include <ctype.h>

int isprint(int c) {
  char ch = (char)c;
  return ch >= 0x1f && ch < 0x7f /*DEL*/;
}
