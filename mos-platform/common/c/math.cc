#include <math.h>

template <typename T> static inline T _fmax(const T x, const T y) {
  if (isnan(y)) return x;
  // if x is nan, then x > y is false, so the ternary returns y
  return x > y ? x : y;
}

template <typename T> static inline T _fmin(const T x, const T y) {
  if (isnan(y)) return x;
  // if x is nan, then x < y is false, so the ternary returns y
  return x < y ? x : y;
}

extern "C" {
double fmin(double x, double y) { return _fmin<double>(x, y); }
double fmax(double x, double y) { return _fmax<double>(x, y); }
float fminf(float x, float y) { return _fmin<float>(x, y); }
float fmaxf(float x, float y) { return _fmax<float>(x, y); }
}
