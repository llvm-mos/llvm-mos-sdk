// End-to-end test for interrupt_norecurse("__nmi"): the NMI handler and main()
// share a helper whose multiply and divide are compiler-rt libcalls. The NMI
// runs with its own imaginary registers, so it must never disturb main()'s
// computation, no matter where it interrupts it.

#include <nes.h>
#include <stdint.h>
#include <stdlib.h>

static volatile uint8_t frames;
static volatile uint16_t nmi_sink;
static volatile uint16_t seed = 12345;

__attribute__((noinline)) static uint16_t mix(uint16_t a, uint16_t b) {
  uint16_t r = a * b + 7;
  r ^= r >> 3;
  r += r / ((b & 0x7f) | 1);
  return r;
}

__attribute__((interrupt_norecurse("__nmi"))) void nmi(void) {
  ++frames;
  nmi_sink = mix(frames, nmi_sink | 3);
}

static uint16_t run(void) {
  uint16_t acc = seed;
  for (uint16_t i = 0; i < 3000; ++i)
    acc = mix(acc, i) ^ i;
  return acc;
}

int main(void) {
  // Reference result, with NMIs off.
  uint16_t expected = run();

  // The same computation, spanning many frames with NMIs on.
  uint8_t start = frames;
  PPU.control = 0x80;
  uint16_t actual = run();
  PPU.control = 0x00;

  if (actual != expected)
    return EXIT_FAILURE;
  // The NMI must actually have run, several times.
  if ((uint8_t)(frames - start) < 4)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
