#include "divmod_m65.h"

#ifndef __SLOW_DIV

template <typename T> static T mul(T a, T b) {
  if constexpr (sizeof(T) <= 4) {
    // ≤32 bit multiplication in hardware
    T product;
    do {
      _MATH_IN_PROGRESS = 1;
      MULTINA = a;
      MULTINB = b;
      product = MULTOUT;
    } while (_MATH_IN_PROGRESS == 0);
    _MATH_IN_PROGRESS = 0;
    return product;
  } else {
    // 64 bit multiplication in software
    T product = 0;
    while (b) {
      if (b & 1)
        product += a;
      a <<= 1;
      b >>= 1;
    }
    return product;
  }
}

extern "C" {

char __mulqi3(char a, char b) { return mul(a, b); }

unsigned __mulhi3(unsigned a, unsigned b) { return mul(a, b); }

unsigned long __mulsi3(unsigned long a, unsigned long b) { return mul(a, b); }

unsigned long long __muldi3(unsigned long long a, unsigned long long b) {
  return mul(a, b);
}
}

#endif