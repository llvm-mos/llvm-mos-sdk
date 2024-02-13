// Stub implementation of math.h.

#ifndef _MATH_H_
#define _MATH_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FP_NORMAL 0
#define FP_SUBNORMAL 1
#define FP_ZERO 2
#define FP_INFINITE 3
#define FP_NAN 4

#define INFINITY (1.0f / 0.0f)

#define isnan(arg) __builtin_isnan(arg)

double fmin(double x, double y);
double fmax(double x, double y);
float fminf(float x, float y);
float fmaxf(float x, float y);

#ifdef __cplusplus
}
#endif

#endif // not _MATH_H_
