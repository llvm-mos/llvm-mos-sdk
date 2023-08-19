#define MULTINA 0xD770
#define MULTINB 0xD774
#define MULTOUT 0xD778

// 32-bit unsigned integer multiplication using MEGA65 accelerated math
// registers
template <typename T> static inline T mul_m65(T a, T b) {
  *(volatile T *)(MULTINA) = a;
  *(volatile T *)(MULTINB) = b;
  return *(volatile T *)(MULTOUT);
}

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

inline char __mulqi3(char a, char b) { return mul_m65(a, b); }

unsigned __mulhi3(unsigned a, unsigned b) { return mul_m65(a, b); }

unsigned long __mulsi3(unsigned long a, unsigned long b) { return mul_m65(a, b); }

unsigned long long __muldi3(unsigned long long a, unsigned long long b) {
  return mul(a, b);
}
}
