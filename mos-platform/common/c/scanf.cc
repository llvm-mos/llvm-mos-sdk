// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdio.h>

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "varint.h"

// Originally from the Public Domain C Library (PDCLib)

using namespace __impl;

namespace {

/* Using an integer's bits as flags for both the conversion flags and length
 modifiers.
*/
#define E_suppressed 1 << 0

/* Helper function to get a character from the string or stream, whatever is
   used for input. When reading from a string, returns EOF on end-of-string
   so that handling of the return value can be uniform for both streams and
   strings.
*/
int get(Status *status) {
  int rc = EOF;

  if (status->s != NULL)
    rc = (*status->s == '\0') ? EOF : (unsigned char)*((status->s)++);
  else
    rc = getchar();

  if (rc != EOF) {
    status->i++;
    status->current++;
  }

  return rc;
}

/* Helper function to put a read character back into the string or stream,
   whatever is used for input.
*/
void unget(int c, Status *status) {
  if (status->s != NULL)
    --(status->s);
  else
    ungetc(c, stdin); /* TODO: Error? */

  status->i--;
  status->current--;
}

/* Helper function to check if a character is part of a given scanset */
bool in_scanset(const char *scanlist, const char *end_scanlist, int rc) {
  /* SOLAR */
  int previous = -1;

  while (scanlist != end_scanlist) {
    if (*scanlist == '-' && previous != -1) {
      /* possible scangroup ("a-z") */
      if (++scanlist == end_scanlist) {
        /* '-' at end of scanlist does not describe a scangroup */
        return rc == '-';
      }

      while (++previous <= (unsigned char)*scanlist)
        if (previous == rc)
          return true;

      previous = -1;
    } else {
      /* not a scangroup, check verbatim */
      if (rc == (unsigned char)*scanlist)
        return true;

      previous = (unsigned char)(*scanlist++);
    }
  }

  return false;
}

const char *scan(const char *spec, Status *status) {
  /* generic input character */
  int rc;
  const char *prev_spec;
  const char *orig_spec = spec;
  bool value_parsed;

  if (*++spec == '%') {
    /* %% -> match single '%' */
    rc = get(status);

    switch (rc) {
    case EOF:
      /* input error */
      if (status->n == 0)
        status->n = -1;
      return NULL;

    case '%':
      return ++spec;

    default:
      unget(rc, status);
      break;
    }
  }

  /* Initializing status structure */
  status->flags = 0;
  status->base = -1;
  status->current = 0;
  status->width = 0;
  status->prec = 0;

  /* '*' suppresses assigning parsed value to variable */
  if (*spec == '*') {
    status->flags |= E_suppressed;
    ++spec;
  }

  /* If a width is given, __simple__strtoui() will return its value. If not
     given, it returns zero. In both cases, endptr will point to the rest of the
     conversion specifier - just what we need.
  */
  prev_spec = spec;
  status->width = __simple_strtoui(spec, (char **)&spec);

  if (spec == prev_spec)
    status->width = SIZE_MAX;

  /* Optional length modifier
     We step one character ahead in any case, and step back only if we find
     there has been no length modifier (or step ahead another character if it
     has been "hh" or "ll").
  */
  size_t size = sizeof(int);
  switch (*spec++) {
  case 'h':
    if (*spec == 'h') {
      /* hh -> char */
      size = sizeof(char);
      ++spec;
    } else {
      /* h -> short == int */
    }
    break;

  case 'l':
    if (*spec == 'l') {
      size = sizeof(long long);
      /* ll -> long long */
      ++spec;
    } else {
      /* l -> long */
      size = sizeof(long);
    }
    break;

  case 'j':
    /* j -> intmax_t, which might or might not be long long */
    size = sizeof(long long);
    break;

  case 'z':
    /* z -> size_t == unsigned */
    break;

  case 't':
    /* t -> ptrdiff_t == int */
    break;

  case 'L':
    /* L -> long double == double */
    break;

  default:
    --spec;
    break;
  }

  /* Conversion specifier */

  /* whether valid input had been parsed */
  value_parsed = false;

  switch (*spec) {
  case 'u':
  case 'd':
    status->base = 10;
    break;

  case 'i':
    status->base = 0;
    break;

  case 'o':
    status->base = 8;
    break;

  case 'x':
    status->base = 16;
    break;

  case 'f':
  case 'F':
  case 'e':
  case 'E':
  case 'g':
  case 'G':
  case 'a':
  case 'A':
    break;

  case 'c': {
    char *c = NULL;

    if (!(status->flags & E_suppressed))
      c = va_arg(status->arg, char *);

    /* for %c, default width is one */
    if (status->width == SIZE_MAX)
      status->width = 1;

    /* reading until width reached or input exhausted */
    while (status->current < status->width && (rc = get(status)) != EOF) {
      if (c != NULL)
        *c++ = rc;

      value_parsed = true;
    }

    /* width or input exhausted */
    if (value_parsed) {
      if (c != NULL)
        ++status->n;
      return ++spec;
    } else {
      /* input error, no character read */
      if (status->n == 0)
        status->n = -1;
      return NULL;
    }
  }

  case 's': {
    char *c = NULL;

    if (!(status->flags & E_suppressed))
      c = va_arg(status->arg, char *);

    while (status->current < status->width && (rc = get(status)) != EOF) {
      if (isspace(rc)) {
        unget(rc, status);

        if (value_parsed) {
          /* matching sequence terminated by whitespace */
          if (c != NULL) {
            *c = '\0';
            ++status->n;
          }

          return ++spec;
        } else {
          /* matching error */
          return NULL;
        }
      } else {
        /* match */
        if (c != NULL)
          *c++ = rc;

        value_parsed = true;
      }
    }

    /* width or input exhausted */
    if (value_parsed) {
      if (c != NULL) {
        *c = '\0';
        ++status->n;
      }

      return ++spec;
    } else {
      /* input error, no character read */
      if (status->n == 0)
        status->n = -1;
      return NULL;
    }
  }

  case '[': {
    const char *endspec = spec;
    bool negative_scanlist = false;
    char *c = NULL;

    if (!(status->flags & E_suppressed))
      c = va_arg(status->arg, char *);

    if (*++endspec == '^') {
      negative_scanlist = true;
      ++endspec;
    }

    spec = endspec;

    do {
      /* TODO: This can run beyond a malformed format string */
      ++endspec;
    } while (*endspec != ']');

    /* read according to scanlist, equiv. to %s above */
    while (status->current < status->width && (rc = get(status)) != EOF) {
      if (negative_scanlist) {
        if (in_scanset(spec, endspec, rc)) {
          unget(rc, status);
          break;
        }
      } else {
        if (!in_scanset(spec, endspec, rc)) {
          unget(rc, status);
          break;
        }
      }

      if (c != NULL)
        *c++ = rc;
      value_parsed = true;
    }

    /* width or input exhausted */
    if (value_parsed) {
      if (c != NULL) {
        *c = '\0';
        ++status->n;
      }

      return ++endspec;
    } else {
      if (status->n == 0)
        status->n = -1;
      return NULL;
    }
  }

  case 'p':
    status->base = 16;
    break;

  case 'n': {
    if (!(status->flags & E_suppressed)) {
      int *val = va_arg(status->arg, int *);
      *val = status->i;
    }

    return ++spec;
  }

  default:
    /* No conversion specifier. Bad conversion. */
    return orig_spec;
  }

  if (status->base != -1) {
    /* integer conversion */
    char space[sizeof(BigInt<sizeof(long long)>)];

    VarInt &value = VarInt::make(space, size);
    value.zero();

    bool prefix_parsed = false;
    signed char sign = 0;

    while (status->current < status->width && (rc = get(status)) != EOF) {
      if (isspace(rc)) {
        if (sign) {
          /* matching sequence terminated by whitespace */
          unget(rc, status);
          break;
        } else {
          /* leading whitespace not counted against width */
          status->current--;
        }
      } else {
        if (!sign) {
          /* no sign parsed yet */
          switch (rc) {
          case '-':
            sign = -1;
            break;

          case '+':
            sign = 1;
            break;

          default:
            /* not a sign; put back character */
            sign = 1;
            unget(rc, status);
            break;
          }
        } else {
          if (!prefix_parsed) {
            /* no prefix (0x... for hex, 0... for octal) parsed yet */
            prefix_parsed = true;

            if (rc != '0') {
              /* not a prefix; if base not yet set, set to decimal */
              if (status->base == 0) {
                status->base = 10;
              }

              unget(rc, status);
            } else {
              /* starts with zero, so it might be a prefix. */
              /* check what follows next (might be 0x...) */
              if (status->current < status->width &&
                  (rc = get(status)) != EOF) {
                if (tolower(rc) == 'x') {
                  /* 0x... would be prefix for hex base... */
                  if ((status->base == 0) || (status->base == 16)) {
                    status->base = 16;
                  } else {
                    /* ...unless already set to other value */
                    unget(rc, status);
                    value_parsed = true;
                  }
                } else {
                  /* 0... but not 0x.... would be octal prefix */
                  unget(rc, status);

                  if (status->base == 0)
                    status->base = 8;

                  /* in any case we have read a zero */
                  value_parsed = true;
                }
              } else {
                /* failed to read beyond the initial zero */
                value_parsed = true;
                break;
              }
            }
          } else {
            signed char digit = __parse_digit(rc, status->base);

            if (digit < 0) {
              /* end of input item */
              unget(rc, status);
              break;
            }

            value *= status->base;
            value += digit;
            value_parsed = true;
          }
        }
      }
    }

    /* width or input exhausted, or non-matching character */
    if (!value_parsed) {
      /* out of input before anything could be parsed - input error */
      /* FIXME: if first character does not match, value_parsed is not set - but
       * it is NOT an input error */
      if (status->n == 0 && rc == EOF)
        status->n = -1;

      return NULL;
    }

    /* convert value to target type and assign to parameter */
    if (!(status->flags & E_suppressed)) {
      if (sign == -1)
        value.negate();
      // Undefined behavior, but should be fine; we're the compiler.
      void *dst = va_arg(status->arg, void *);
      memcpy(dst, value.bytes(), value.size());
      ++status->n;
    }

    return ++spec;
  }

  /* TODO: Floats. */
  return NULL;
}

} // namespace

extern "C" {

int fscanf(FILE *__restrict__ stream, const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vfscanf(stream, format, ap);
  va_end(ap);
  return rc;
}

int scanf(const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vfscanf(stdin, format, ap);
  va_end(ap);
  return rc;
}

int sscanf(const char *__restrict__ s, const char *__restrict__ format, ...) {
  int rc;
  va_list ap;
  va_start(ap, format);
  rc = vsscanf(s, format, ap);
  va_end(ap);
  return rc;
}

int vfscanf(FILE *__restrict__ stream, const char *__restrict__ format,
            va_list arg) {
  /* TODO: This function should interpret format as multibyte characters.  */
  Status status;
  status.base = 0;
  status.flags = 0;
  status.n = 0;
  status.i = 0;
  status.s = NULL;
  status.width = 0;
  status.prec = EOF;

  va_copy(status.arg, arg);

  while (*format != '\0') {
    const char *rc;

    if ((*format != '%') || ((rc = scan(format, &status)) == format)) {
      int c;

      /* No conversion specifier, match verbatim */
      if (isspace(*format)) {
        /* Whitespace char in format string: Skip all whitespaces */
        /* No whitespaces in input does not result in matching error */
        while (isspace(c = getc(stream))) {
          ++status.i;
        }

        if (!feof(stream)) {
          ungetc(c, stream);
        }
      } else {
        /* Non-whitespace char in format string: Match verbatim */
        if (((c = getc(stream)) != *format) || feof(stream)) {
          /* Matching error */
          if (!feof(stream) && !ferror(stream)) {
            ungetc(c, stream);
          } else if (status.n == 0) {
            return EOF;
          }

          return status.n;
        } else {
          ++status.i;
        }
      }

      ++format;
    } else {
      /* NULL return code indicates matching error */
      if (rc == NULL) {
        break;
      }

      /* Continue parsing after conversion specifier */
      format = rc;
    }
  }

  va_end(status.arg);
  return status.n;
}

int vscanf(const char *__restrict__ format, va_list arg) {
  return vfscanf(stdin, format, arg);
}

int vsscanf(const char *__restrict__ s, const char *__restrict__ format,
            va_list arg) {
  /* TODO: This function should interpret format as multibyte characters.  */
  Status status;
  status.base = 0;
  status.flags = 0;
  status.n = 0;
  status.i = 0;
  status.s = (char *)s;
  status.width = 0;
  status.prec = EOF;
  va_copy(status.arg, arg);

  while (*format != '\0') {
    const char *rc;

    if ((*format != '%') || ((rc = scan(format, &status)) == format)) {
      /* No conversion specifier, match verbatim */
      if (isspace(*format)) {
        /* Whitespace char in format string: Skip all whitespaces */
        /* No whitespaces in input do not result in matching error */
        while (isspace(*status.s)) {
          ++status.s;
          ++status.i;
        }
      } else {
        /* Non-whitespace char in format string: Match verbatim */
        if (*status.s != *format) {
          if (*status.s == '\0' && status.n == 0) {
            /* Early input error */
            return EOF;
          }

          /* Matching error */
          return status.n;
        } else {
          ++status.s;
          ++status.i;
        }
      }

      ++format;
    } else {
      /* NULL return code indicates error */
      if (rc == NULL) {
        if (*status.s == '\n' && status.n == 0) {
          status.n = EOF;
        }

        break;
      }

      /* Continue parsing after conversion specifier */
      format = rc;
    }
  }

  va_end(status.arg);
  return status.n;
}

} // extern "C"
