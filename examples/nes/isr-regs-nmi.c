#include <nes.h>
#include <stdint.h>

/**
 * Demonstration for the suffixed `interrupt_norecurse` function attribute.
 * Adding a suffix parameter to this attr creates clones the call tree and
 * all registers used, so that the ISR contains a completely independent
 * set of imaginary registers. Without a suffix, the compiler has to defensively
 * create a large list of register save/restores for the interrupt, which is
 * not good for interrupts that need to fire and quit as fast as possible.
 * With this approach, only the a/x/y registers are preserved by default.
 */

static volatile uint8_t frame_counter;

static void wait_nmi(void) {
  uint8_t tmp = frame_counter;
  while (tmp == frame_counter)
    ;
}

/**
 * Example function called from both the MAIN thread and the new __nmi
 * thread, and since its called from both, this will be cloned so that
 * both can call using their own set of imaginary registers.
 */
__attribute__((noinline))
static uint16_t compute(uint16_t a, uint16_t b) {
  uint16_t result = a * b + 7;
  result ^= result >> 3;
  result += result / (b | 1);
  return result;
}

/**
 * Creates a root for the suffixed ISR, all of the registers and functions
 * used in it are cloned so that they do not interfere with anything that
 * the main thread is doing. 
 */
__attribute__((interrupt_norecurse("__nmi")))
void nmi(void) {
  ++frame_counter;
  // Touch a computation that forces cloning of compute().
  volatile uint16_t v = compute(frame_counter, 3);
  (void)v;
}

int main(void) {
  PPU.control = 0x80;

  volatile uint16_t accumulator = 1;
  for (;;) {
    wait_nmi();
    // This call uses the main registers
    accumulator = compute(accumulator, accumulator);
  }
}
