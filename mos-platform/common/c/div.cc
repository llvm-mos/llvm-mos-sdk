#include <stdlib.h>

template <typename T, typename R> static inline R _div(T numer, T denom) {
  R result;
  result.quot = numer / denom;
  result.rem = numer % denom;
  return result;
}

extern "C" {
div_t div(int numer, int denom) { return _div<int, div_t>(numer, denom); }
ldiv_t ldiv(long numer, long denom) { return _div<long, ldiv_t>(numer, denom); }
lldiv_t lldiv(long long numer, long long denom) {
  return _div<long long, lldiv_t>(numer, denom);
}
}
