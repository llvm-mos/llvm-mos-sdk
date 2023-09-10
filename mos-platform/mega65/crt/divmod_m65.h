#pragma once

namespace common {
#include "divmod.h"
}
#include <stdint.h>

#define DIVBUSY (*(volatile uint8_t *)(0xD70F))
#define MULTINA (*(volatile T *)(0xD770))
#define MULTINB (*(volatile T *)(0xD774))
#define MULTOUT (*(volatile T *)(0xD778))
#define DIVOUT_WHOLE (*(volatile T *)(0xD76C))

// State to prevent race conditions on math registers during interrupts
extern __attribute__((section(".zp.bss"))) volatile char _MATH_IN_PROGRESS;

#ifndef __SLOW_DIV

// Interrupt-safe max 32-bit unsigned integer division using MEGA65
// accelerated math registers.
template <typename T> static T udiv_m65(const T a, const T b) {
  static_assert(sizeof(T) <= 4, "integers can be maximum 32-bits");
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

// Relatively straigtforward implementation of long division in C. Not
// particularly tuned for performance, but clear.

template <typename T> static inline T udiv(T a, T b) {
  if constexpr (sizeof(T) > 4) {
    return common::udiv(a, b);
  } else {
    return udiv_m65(a, b);
  }
}

template <typename T> static inline T umod_m65(T a, T b) {
  static_assert(sizeof(T) <= 4, "integers can be maximum 32-bits");
  if (b == 0) {
    // the math register does nothing if b==0 so we must catch this
    return 0;
  }
  T q = udiv_m65(a, b);
  return (q != 0) ? a - q * b : a;
}

template <typename T> static inline T umod(T a, T b) {
  if constexpr (sizeof(T) > 4) {
    return common::umod(a, b);
  } else {
    return umod_m65(a, b);
  }
}

template <typename T> static inline T udivmod(T a, T b, T *rem) {
  if constexpr (sizeof(T) > 4) {
    return common::udivmod(a, b, rem);
  } else {
    if (b != 0) {
      T q = udiv_m65(a, b);
      *rem = (q != 0) ? a - q * b : a;
      return q;
    } else {
      // the math register does nothing if b==0 so we must catch this
      *rem = 0;
      return 0;
    }
  }
}

#endif // __SLOW_DIV

template <typename T> static inline T div(T a, T b) {
  T u = static_cast<T>(common::safe_abs(a) / common::safe_abs(b));
  // Negating int_min here is fine, since it's only undefined behavior if the
  // signed division itself is.
  return (a < 0 != b < 0) ? -u : u;
}

template <typename T> static inline T mod(T a, T b) {
  T u = static_cast<T>(common::safe_abs(a) % common::safe_abs(b));
  // Negating int_min here is fine, since it's only undefined behavior if the
  // signed mod itself is.
  return a < 0 ? -u : u;
}

template <typename T> static inline T divmod(T a, T b, T *rem) {
  typedef typename common::make_unsigned<T>::type UT;
  UT urem;
  T uq =
      static_cast<T>(udivmod(common::safe_abs(a), common::safe_abs(b), &urem));

  // Negating int_min here is fine, since it's only undefined behavior if the
  // signed division itself is.
  *rem = a < 0 ? -urem : urem;
  return (a < 0 != b < 0) ? -uq : uq;
}