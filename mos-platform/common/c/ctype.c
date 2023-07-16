#include <ctype.h>

int isalnum(int c) { return isalpha(c) || isdigit(c); }

int isalpha(int c) {
  char ch = (char)c;
  return ((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'));
}

int isblank(int c) {
  char ch = (char)c;
  return ch == ' ' || ch == '\t';
}

int iscntrl(int c) {
  char ch = (char)c;
  return ch < ' ';
}

int isdigit(int c) {
  char ch = (char)c;
  return ch >= '0' && ch <= '9';
}

int isgraph(int c) {
  char ch = (char)c;
  return isprint(c) && (c != ' ');
}

int islower(int c) {
  char ch = (char)c;
  return ch >= 'a' && ch <= 'z';
}

int isprint(int c) {
  char ch = (char)c;
  return ch > 0x1f && ch < 0x7f /*DEL*/;
}

int ispunct(int c) { return isprint(c) && !isspace(c) && !isalnum(c); }

int isspace(int c) {
  char ch = c;
  return (ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\f') ||
         (ch == '\r') || (ch == '\v');
}

int isupper(int c) {
  char ch = (char)c;
  return ch >= 'A' && ch <= 'Z';
}

int isxdigit(int c) {
  char ch = (char)c;
  return ((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) ||
         ((ch >= 'A') && (ch <= 'F'));
}

int tolower(int c) {
  char ch = (char)c;
  if ((ch >= 'A') && (ch <= 'Z'))
    ch |= 0x20;
  return ch;
}

int toupper(int c) {
  char ch = (char)c;
  if ((ch >= 'a') && (ch <= 'z'))
    ch &= ~0x20;
  return ch;
}
