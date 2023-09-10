#pragma once

#ifndef __SLOW_DIV

#include <stdint.h>

#define MULTINA 0xD770
#define MULTINB 0xD774
#define MULTOUT (*(volatile T *)(0xD778))
#define DIVBUSY (*(volatile uint8_t *)(0xD70F))
#define DIVOUT_WHOLE (*(volatile T *)(0xD76C))
#define INTEGER_TOO_BIG "MEGA65 math register can take maximum 32-bit integers"

// State to prevent race conditions on math registers during interrupts
__attribute__((section(".zp.bss"))) volatile char _MATH_IN_PROGRESS = 0;

namespace common::crt {
#include "divmod.h"
}

namespace mega65::crt {

template <typename T> static T mul(T a, T b) {
  static_assert(sizeof(T) <= 4, INTEGER_TOO_BIG);
  T product;
  do {
    _MATH_IN_PROGRESS = 1;
    (*(volatile T *)(MULTINA)) = a;
    (*(volatile T *)(MULTINB)) = b;
    product = MULTOUT;
  } while (_MATH_IN_PROGRESS == 0);
  _MATH_IN_PROGRESS = 0;
  return product;
}

// Interrupt-safe max 32-bit unsigned integer division using MEGA65
// accelerated math registers.
template <typename T> static T udiv(const T a, const T b) {
  static_assert(sizeof(T) <= 4, INTEGER_TOO_BIG);
  if (b == 0) {
    return 0;
  }
  T result;
  do {
    _MATH_IN_PROGRESS = 1;
    (*(volatile uint32_t *)(MULTINA)) = (uint32_t)a;
    (*(volatile uint32_t *)(MULTINB)) = (uint32_t)b;
    while (DIVBUSY) {
    };
    result = DIVOUT_WHOLE;
  } while (_MATH_IN_PROGRESS == 0);
  _MATH_IN_PROGRESS = 0;
  return result;
}

template <typename T> static inline T umod(T a, T b) {
  static_assert(sizeof(T) <= 4, INTEGER_TOO_BIG);
  if (b == 0) {
    // the math register does nothing if b==0 so we must catch this
    return 0;
  }
  T q = udiv(a, b);
  return (q != 0) ? a - q * b : a;
}

template <typename T> static inline T udivmod(T a, T b, T *rem) {
  static_assert(sizeof(T) <= 4, INTEGER_TOO_BIG);
  if (b != 0) {
    T q = udiv(a, b);
    *rem = (q != 0) ? a - q * b : a;
    return q;
  }
  // the math register does nothing if b==0 so we must catch this
  *rem = 0;
  return 0;
}

} // namespace mega65::crt

template <typename T> static inline T udiv(T a, T b) {
  if constexpr (sizeof(T) > 4) {
    return common::crt::udiv(a, b);
  } else {
    return mega65::crt::udiv(a, b);
  }
}

template <typename T> static inline T umod(T a, T b) {
  if constexpr (sizeof(T) > 4) {
    return common::crt::umod(a, b);
  } else {
    return mega65::crt::umod(a, b);
  }
}

template <typename T> static inline T udivmod(T a, T b, T *rem) {
  if constexpr (sizeof(T) > 4) {
    return common::crt::udivmod(a, b, rem);
  } else {
    return mega65::crt::udivmod(a, b, rem);
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
