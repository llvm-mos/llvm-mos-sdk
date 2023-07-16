/**
 * color-cycle-banked
 *
 * To the extent possible under law, the person who associated CC0 with
 * color-cycle has waived all copyright and related or neighboring rights
 * to color-cycle.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

// Make sure to define this in only one compilation unit, *before* including
// the pce.h header.
#define PCE_CONFIG_IMPLEMENTATION

#include <pce.h>

// Declare physical bank 1 to be at offset 0xC000.
PCE_ROM_BANK_AT(1, 6);

static uint16_t color;

__attribute__((noinline, section(".rom_bank1"))) void cycle_color(void) {
  *IO_VCE_COLOR_INDEX = 0x100;
  *IO_VCE_COLOR_DATA = color++;
}

int main(void) {
  pce_rom_bank1_map();

  while (1) {
    cycle_color();
  }
}
