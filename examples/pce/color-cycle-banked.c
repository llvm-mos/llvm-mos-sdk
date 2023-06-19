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
#define PCE_VBANK_IMPLEMENTATION

#include <stdio.h>
#include <pce.h>

// Define a PCE virtual bank 1, with offset 6 (0xC000) and size 1 (8KB).
PCE_ROM_VBANK_DEFINE(1, 6, 1);

static uint16_t color;

__attribute__((noinline, section(".rom_vbank_1")))
void cycle_color(void) {
	*IO_VCE_COLOR_INDEX = 0x100;
	*IO_VCE_COLOR_DATA = color++;
}

int main(void) {
	pce_vbank1_set();

	while(1) {
		cycle_color();
	}
}
