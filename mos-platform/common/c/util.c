#include "util.h"

#include <ctype.h>

signed char __parse_digit(char c, char base) {
  if (!isalnum(c))
    return -1;
  if (isdigit(c)) {
    signed char val = c - '0';
    return val < base ? val : -1;
  }
  signed char val = tolower(c) - 'a' + 10;
  return val < base ? val : -1;
}

unsigned __simple_strtoui(const char *__restrict__ nptr,
                          char **__restrict endptr) {
  unsigned result = 0;

  for (*endptr = (char *)nptr; **endptr && '0' <= **endptr && **endptr <= '9';
       ++*endptr) {
    result *= 10;
    result += **endptr - '0';
  }

  return result;
}
