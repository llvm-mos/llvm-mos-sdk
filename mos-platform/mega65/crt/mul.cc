#define MULTINA 0xD770
#define MULTINB 0xD774
#define MULTOUT 0xD778

// Used to lock math register access if interrupts
__attribute__((section(".zp.bss"))) volatile char _IN_PROGRESS = 0;

template <typename T> static inline T mul(T a, T b) {
  // 32-bit unsigned integer multiplication using hardware math registers
  if constexpr (sizeof(T) <= 4) {
    T product;
    do {
      _IN_PROGRESS = 1;
      *(volatile T *)(MULTINA) = a;
      *(volatile T *)(MULTINB) = b;
      product = *(volatile T *)(MULTOUT);
    } while (!_IN_PROGRESS);
    _IN_PROGRESS = 0;
    return product;
  }

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
