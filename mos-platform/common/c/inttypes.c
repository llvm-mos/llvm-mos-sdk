#include <inttypes.h>

intmax_t imaxabs(intmax_t j) {
  return __builtin_llabs(j);
}

imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom) {
  imaxdiv_t result = {numer / denom, numer % denom};
  return result;
}
