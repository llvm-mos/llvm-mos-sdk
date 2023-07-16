/**
 * color-cycle
 *
 * To the extent possible under law, the person who associated CC0 with
 * color-cycle has waived all copyright and related or neighboring rights
 * to color-cycle.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <pce.h>

uint16_t ticks = 0;

// Define a VDC interrupt handler.
__attribute__((interrupt)) void irq_vdc(void) {
  // This also acknowledges the interrupt.
  uint8_t status = *IO_VDC_STATUS;

  if (status & VDC_FLAG_VBLANK) {
    ticks++;
  }
}

int main(void) {
  // Configure the VDC screen resolution.
  pce_vdc_set_resolution(256, 240, 0);

  // Enable VDC interrupts for VBlanks.
  pce_vdc_irq_vblank_enable();
  pce_irq_enable(IRQ_VDC);
  pce_cpu_irq_enable();

  while (1) {
    *IO_VCE_COLOR_INDEX = 0x100;
    *IO_VCE_COLOR_DATA = (ticks >> 3);
  }
}
