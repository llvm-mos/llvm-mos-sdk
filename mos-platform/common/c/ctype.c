#include <ctype.h>

int isprint(int c) {
  char ch = (char)c;
  return ch >= 0x1f && ch < 0x7f /*DEL*/;
}

int isdigit(int c) {
  char ch = (char)c;
  return ch >= '0' && ch <= '9';
}

int isalpha(int c) {
  char ch = (char)c;
  return ((ch >= 'A') && (ch <= 'Z'))
    || ((ch >= 'a') && (ch <= 'z'));
}

int toupper(int c) {
  char ch = (char)c;
  if ((ch >= 'a') && (ch <= 'z'))
    ch &= ~0x20;
  return ch;
}

int isalnum(int c) {
  return isalpha(c) || isdigit(c);
}

int isspace(int c) {
  char ch = c;
  return (ch == ' ') || (ch == '\t') || (ch == '\n') ||
  	(ch == '\f') || (ch == '\r') || (ch == '\v');
}

