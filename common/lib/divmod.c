// These are just temporary; writing a good division algorithm is quite
// difficult, and branchless off-the-shelf ones are likely to do quite poorly
// on the 6502. We should iron out as many compiler bugs as we can before
// tuning division, since it's sure to be a grueling process.

unsigned long __udivsi3(unsigned long a, unsigned long b) {
  unsigned long q = 0;
  while (a >= b) {
    a -= b;
    q++;
  }
  return q;
}

unsigned long __umodsi3(unsigned long a, unsigned long b) {
  while (a >= b)
    a -= b;
  return a;
}
