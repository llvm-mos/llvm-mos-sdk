template <typename T> static inline T shl(T n, char amt) {
  while (amt--)
    n <<= 1;
  return n;
}

template <typename T> static inline T shr(T n, char amt) {
  while (amt--)
    n >>= 1;
  return n;
}

extern "C" {
char __ashlqi3(char n, char amt) { return shl(n, amt); }
unsigned int __ashlhi3(unsigned int n, char amt) { return shl(n, amt); }
unsigned long __ashlsi3(unsigned long n, char amt) { return shl(n, amt); }
unsigned long long __ashldi3(unsigned long long n, char amt) {
  return shl(n, amt);
}

char __lshrqi3(char n, char amt) { return shr(n, amt); }
unsigned int __lshrhi3(unsigned int n, char amt) { return shr(n, amt); }
unsigned long __lshrsi3(unsigned long n, char amt) { return shr(n, amt); }
unsigned long long __lshrdi3(unsigned long long n, char amt) {
  return shr(n, amt);
}

signed char __ashrqi3(signed char n, char amt) { return shr(n, amt); }
int __ashrhi3(int n, char amt) { return shr(n, amt); }
long __ashrsi3(long n, char amt) { return shr(n, amt); }
long long __ashrdi3(long long n, char amt) { return shr(n, amt); }
}
