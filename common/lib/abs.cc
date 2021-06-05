#include <stdlib.h>

template <typename T> static inline T _abs(T i) { return i < 0 ? -i : i; }

extern "C" {
int abs(int i) { return _abs(i); }
long labs(long i) { return _abs(i); }
long long llabs(long long i) { return _abs(i); }
}
