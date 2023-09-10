#include "fast_math.h"

#ifndef __SLOW_DIV

template <typename T> static T mul(T a, T b) {
  if constexpr (sizeof(T) <= 4) {
    return mega65::crt::mul(a, b);
  } else {
    // 64 bit multiplication in software
    // This could be optimised further by splitting the 64 bit values into
    // 32 bit chunks and using the 32 bit multiplication routine above.
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

char __udivqi3(char a, char b) { return udiv(a, b); }
unsigned __udivhi3(unsigned a, unsigned b) { return udiv(a, b); }
unsigned long __udivsi3(unsigned long a, unsigned long b) { return udiv(a, b); }
unsigned long long __udivdi3(unsigned long long a, unsigned long long b) {
  return udiv(a, b);
}

char __umodqi3(char a, char b) { return umod(a, b); }
unsigned __umodhi3(unsigned a, unsigned b) { return umod(a, b); }
unsigned long __umodsi3(unsigned long a, unsigned long b) { return umod(a, b); }
unsigned long long __umoddi3(unsigned long long a, unsigned long long b) {
  return umod(a, b);
}

char __udivmodqi4(char a, char b, char *rem) { return udivmod(a, b, rem); }
unsigned __udivmodhi4(unsigned a, unsigned b, unsigned *rem) {
  return udivmod(a, b, rem);
}

signed char __divqi3(signed char a, signed char b) { return div(a, b); }
int __divhi3(int a, int b) { return div(a, b); }
long __divsi3(long a, long b) { return div(a, b); }
long long __divdi3(long long a, long long b) { return div(a, b); }

signed char __modqi3(signed char a, signed char b) { return mod(a, b); }
int __modhi3(int a, int b) { return mod(a, b); }
long __modsi3(long a, long b) { return mod(a, b); }
long long __moddi3(long long a, long long b) { return mod(a, b); }

signed char __divmodqi4(signed char a, signed char b, signed char *rem) {
  return divmod(a, b, rem);
}
int __divmodhi4(int a, int b, int *rem) { return divmod(a, b, rem); }
}

#endif