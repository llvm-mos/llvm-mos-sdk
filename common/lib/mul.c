unsigned __mulhi3(unsigned a, unsigned b) {
  unsigned result = 0;
  unsigned shifted_a = a;
  while (b) {
    if (b & 1)
      result += shifted_a;
    shifted_a <<= 1;
    b >>= 1;
  }
  return result;
}
