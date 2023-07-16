template <typename T> static inline T mul(T a, T b) {
  T result = 0;
  while (b) {
    if (b & 1)
      result += a;
    a <<= 1;
    b >>= 1;
  }
  return result;
}

extern "C" {

char __mulqi3(char a, char b) { return mul(a, b); }

unsigned __mulhi3(unsigned a, unsigned b) { return mul(a, b); }

unsigned long __mulsi3(unsigned long a, unsigned long b) { return mul(a, b); }

unsigned long long __muldi3(unsigned long long a, unsigned long long b) {
  return mul(a, b);
}
}
