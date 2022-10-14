template <typename T> static inline T rotl(T n, char amt) {
  while (amt--)
    n = n << 1 | n >> (sizeof(T) * 8 - 1);
  return n;
}

template <typename T> static inline T rotr(T n, char amt) {
  while (amt--)
    n = n >> 1 | n << (sizeof(T) * 8 - 1);
  return n;
}

extern "C" {
char __rotlqi3(char n, char amt) { return rotl(n, amt); }
unsigned int __rotlhi3(unsigned int n, char amt) { return rotl(n, amt); }
unsigned long __rotlsi3(unsigned long n, char amt) { return rotl(n, amt); }
unsigned long long __rotldi3(unsigned long long n, char amt) {
  return rotl(n, amt);
}

char __rotrqi3(char n, char amt) { return rotr(n, amt); }
unsigned int __rotrhi3(unsigned int n, char amt) { return rotr(n, amt); }
unsigned long __rotrsi3(unsigned long n, char amt) { return rotr(n, amt); }
unsigned long long __rotrdi3(unsigned long long n, char amt) {
  return rotr(n, amt);
}
}
