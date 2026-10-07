#include <nes.h>
#include <stdint.h>

// Example: private ISR registers with interrupt_norecurse("__nmi").
//
// This NMI handler uses private imaginary registers (__rc0__nmi ..
// __rc31__nmi) so it need only save A/X/Y. The helper below is called from both
// the ISR tree and mainline code, so the compiler clones it per suffix at LTO
// time. main()'s results are not corrupted even though the handler runs at any
// time.

static volatile uint8_t frame_counter;

static void wait_nmi(void) {
  uint8_t tmp = frame_counter;
  while (tmp == frame_counter)
    ;
}

// A helper that uses imaginary registers and is shared between mainline and
// the ISR tree. The LTO clone pass creates a __nmi-suffixed copy for the ISR.
// The multiply and divide become compiler-rt libcalls, which are cloned for
// the ISR too.
__attribute__((noinline))
static uint16_t compute(uint16_t a, uint16_t b) {
  uint16_t result = a * b + 7;
  result ^= result >> 3;
  result += result / (b | 1);
  return result;
}

// NMI handler: runs once per frame via the NES PPU NMI.
__attribute__((interrupt_norecurse("__nmi")))
void nmi(void) {
  ++frame_counter;
  // Touch a computation that forces cloning of compute().
  volatile uint16_t v = compute(frame_counter, 3);
  (void)v;
}

int main(void) {
  // Enable NMI.
  PPU.control = 0x80;

  uint16_t accumulator = 1;
  for (;;) {
    wait_nmi();
    // This call uses the main registers; the ISR's copy is separate.
    accumulator = compute(accumulator, accumulator);
  }
}
