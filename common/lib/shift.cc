template <typename T> static inline T shl(T n, char amt) {
  while (amt--)
    n <<= 1;
  return n;
}

template <typename T> static inline T lshr(T n, char amt) {
  while (amt--)
    n >>= 1;
  return n;
}

template <typename T> static inline T ashr(T n, char amt) {
  while (amt--)
    n = n >> 1 | n & (T)1 << (sizeof(T) * 8 - 1);
  return n;
}

extern "C" {
char __ashlqi3(char n, char amt) { return shl(n, amt); }
unsigned int __ashlhi3(unsigned int n, char amt) { return shl(n, amt); }
unsigned long __ashlsi3(unsigned long n, char amt) { return shl(n, amt); }
unsigned long long __ashldi3(unsigned long long n, char amt) {
  return shl(n, amt);
}

char __lshrqi3(char n, char amt) { return lshr(n, amt); }
unsigned int __lshrhi3(unsigned int n, char amt) { return lshr(n, amt); }
unsigned long __lshrsi3(unsigned long n, char amt) { return lshr(n, amt); }
unsigned long long __lshrdi3(unsigned long long n, char amt) {
  return lshr(n, amt);
}

char __ashrqi3(char n, char amt) { return ashr(n, amt); }
unsigned int __ashrhi3(unsigned int n, char amt) { return ashr(n, amt); }
unsigned long __ashrsi3(unsigned long n, char amt) { return ashr(n, amt); }
unsigned long long __ashrdi3(unsigned long long n, char amt) {
  return ashr(n, amt);
}
}
