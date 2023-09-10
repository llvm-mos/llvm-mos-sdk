#pragma once

#ifndef __SLOW_DIV

// State to prevent race conditions on math registers during interrupts
extern __attribute__((section(".zp.bss"))) volatile char _MATH_IN_PROGRESS;

namespace common::crt {
#include "divmod.h"
} // namespace common::crt
#include <stdint.h>

#define DIVBUSY (*(volatile uint8_t *)(0xD70F))
#define MULTINA (*(volatile T *)(0xD770))
#define MULTINB (*(volatile T *)(0xD774))
#define MULTOUT (*(volatile T *)(0xD778))
#define DIVOUT_WHOLE (*(volatile T *)(0xD76C))
#define INTEGER_TOO_BIG "MEGA65 math register can take maximum 32-bit integers"

// Interrupt-safe max 32-bit unsigned integer division using MEGA65
// accelerated math registers.
template <typename T> static T udiv_m65(const T a, const T b) {
  static_assert(sizeof(T) <= 4, INTEGER_TOO_BIG);
  if (b == 0) {
    return 0;
  }
  T result;
  do {
    _MATH_IN_PROGRESS = 1;
    MULTINA = a;
    MULTINB = b;
    while (DIVBUSY) {
    };
    result = DIVOUT_WHOLE;
  } while (_MATH_IN_PROGRESS == 0);
  _MATH_IN_PROGRESS = 0;
  return result;
}

template <typename T> static inline T udiv(T a, T b) {
  if constexpr (sizeof(T) > 4) {
    return common::crt::udiv(a, b);
  } else {
    return udiv_m65(a, b);
  }
}

template <typename T> static inline T umod_m65(T a, T b) {
  static_assert(sizeof(T) <= 4, INTEGER_TOO_BIG);
  if (b == 0) {
    // the math register does nothing if b==0 so we must catch this
    return 0;
  }
  T q = udiv_m65(a, b);
  return (q != 0) ? a - q * b : a;
}

template <typename T> static inline T umod(T a, T b) {
  if constexpr (sizeof(T) > 4) {
    return common::crt::umod(a, b);
  } else {
    return umod_m65(a, b);
  }
}

template <typename T> static inline T udivmod(T a, T b, T *rem) {
  if constexpr (sizeof(T) > 4) {
    return common::crt::udivmod(a, b, rem);
  } else {
    if (b != 0) {
      T q = udiv_m65(a, b);
      *rem = (q != 0) ? a - q * b : a;
      return q;
    }
    // the math register does nothing if b==0 so we must catch this
    *rem = 0;
    return 0;
  }
}

template <typename T> static inline T div(T a, T b) {
  return common::crt::div<T>(a, b);
}

template <typename T> static inline T mod(T a, T b) {
  return common::crt::mod<T>(a, b);
}

template <typename T> static inline T divmod(T a, T b, T *rem) {
  return common::crt::divmod<T>(a, b, rem);
}

#endif // __SLOW_DIV
