/**
 * Tests various math functions (mul, div, mod)
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

template <class T> void check_eq(T a, T b) {
  (a != b) ? printf("MISMATCH\n") : printf("OK ");
}

int main(void) {
  {
    // 64-bit
    volatile uint64_t a = 100;
    volatile uint64_t b = 2;
    check_eq(a / b, 50ULL);
    check_eq(a * b, 200ULL);
    a = 0xffffeeeeddddcccc;
    b = 0xffffffffaaaabbbb;
    check_eq(a * b, 6886803220519558404ULL);
    check_eq(a / b, 0ULL);
    check_eq(b / a, 1ULL);
    check_eq(a % b, 18446725308424768716ULL);
    check_eq(b % a, 18763853131503ULL);
    a = 3;
    b = 2;
    check_eq(a % b, 1ULL); // 3 & 2
    a = 0;
    b = 2;
    check_eq(a % b, 0ULL); // 0 & 2
    a = 3;
    b = 20;
    check_eq(a % b, 3ULL); // 3 & 20
    a = 20;
    b = 3;
    check_eq(a % b, 2ULL); // 20 & 3
  }

  {
    // 32-bit
    volatile uint32_t a = 100;
    volatile uint32_t b = 2;
    check_eq(a / b, 50UL);
    check_eq(a * b, 200UL);
    a = 0xffffeeee;
    b = 0xffffffff;
    check_eq(a * b, 4370UL);
    check_eq(a / b, 0UL);
    check_eq(b / a, 1UL);
    check_eq(a % b, 4294962926UL);
    check_eq(b % a, 4369UL);
    a = 3;
    b = 2;
    check_eq(a % b, 1UL); // 3 & 2
    a = 0;
    b = 2;
    check_eq(a % b, 0UL); // 0 & 2
    a = 3;
    b = 20;
    check_eq(a % b, 3UL); // 3 & 20
    a = 20;
    b = 3;
    check_eq(a % b, 2UL); // 20 & 3
  }

  // 16-bit
  {
    volatile uint16_t a = 0xeeee;
    volatile uint16_t b = 0xffff;
    check_eq(a * b, 4370U);
    check_eq(a / b, 0U);
    check_eq(b / a, 1U);
    check_eq(a % b, 61166U);
    check_eq(b % a, 4369U);
    a = 100;
    b = 2;
    check_eq(a * b, 200U);
    check_eq(a / b, 50U);
    a = 3;
    b = 2;
    check_eq(a % b, 1U); // 3 & 2
    a = 0;
    b = 2;
    check_eq(a % b, 0U); // 0 & 2
    a = 3;
    b = 20;
    check_eq(a % b, 3U); // 3 & 20
    a = 20;
    b = 3;
    check_eq(a % b, 2U); // 20 & 3
  }

  // 16-bit, signed
  {
    volatile int16_t a = -31166;
    volatile int16_t b = 500;
    check_eq(a * b, 14568);
    check_eq(a / b, -62);
    check_eq(b / a, 0);
    check_eq(a % b, -166);
    check_eq(b % a, 500);
    a = 100;
    b = -2;
    check_eq(a * b, -200);
    check_eq(a / b, -50);
    a = 3;
    b = 2;
    check_eq(a % b, 1); // 3 & 2
    a = 0;
    b = 2;
    check_eq(a % b, 0); // 0 & 2
    a = 3;
    b = 20;
    check_eq(a % b, 3); // 3 & 20
    a = 20;
    b = 3;
    check_eq(a % b, 2); // 20 & 3
  }

  // 8-bit
  {
    volatile uint8_t a = 0xee;
    volatile uint8_t b = 0xff;
    check_eq<uint8_t>((uint8_t)(a * b), 18);
    check_eq<uint8_t>((uint8_t)(a / b), 0);
    check_eq<uint8_t>((uint8_t)(b / a), 1);
    check_eq<uint8_t>((uint8_t)(a % b), 238);
    check_eq<uint8_t>((uint8_t)(b % a), 17);
    a = 3;
    b = 2;
    check_eq(a % b, 1); // 3 & 2
    a = 0;
    b = 2;
    check_eq(a % b, 0); // 0 & 2
    a = 3;
    b = 20;
    check_eq(a % b, 3); // 3 & 20
    a = 20;
    b = 3;
    check_eq(a % b, 2); // 20 & 3
  }
  return 0;
}
