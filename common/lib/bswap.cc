template <typename T> static inline T bswap(T a) {
  union {
    T a;
    char bytes[sizeof(T)];
  } u;
  u.a = a;
  for (int i = 0, j = sizeof(T) - 1; i < j; i++, j--) {
    T tmp = u.bytes[i];
    u.bytes[i] = u.bytes[j];
    u.bytes[j] = tmp;
  }
  return u.a;
}

extern "C" {
char __bswapqi2(char a) { return bswap(a); }
unsigned __bswaphi2(unsigned a) { return bswap(a); }
unsigned long __bswapsi2(unsigned long a) { return bswap(a); }
unsigned long long __bswapdi2(unsigned long long a) { return bswap(a); }
}
