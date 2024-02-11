#include <math.h>

template <typename T> static inline bool _is_nan(const T x) { return x != x; }

template <typename T> static inline T _fmax(const T x, const T y) {
  if (_is_nan(x)) return y;
  if (_is_nan(y)) return x;
  return x > y ? x : y;
}

template <typename T> static inline T _fmin(const T x, const T y) {
  if (_is_nan(x)) return y;
  if (_is_nan(y)) return x;
  return x < y ? x : y;
}

extern "C" {
T fmin(double x, double y) { return _fmin<double>(x, y); }
T fmax(double x, double y) { return _fmax<double>(x, y); }
T fminf(float x, float y) { return _fmin<float>(x, y); }
T fmaxf(float x, float y) { return _fmax<float>(x, y); }
}
