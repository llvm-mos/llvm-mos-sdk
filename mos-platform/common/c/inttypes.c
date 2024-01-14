#include <inttypes.h>

#include <stdlib.h>

intmax_t imaxabs(intmax_t j) { return __builtin_llabs(j); }

imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom) {
  lldiv_t llr = lldiv(numer, denom);
  imaxdiv_t r = {llr.quot, llr.rem};
  return r;
}
