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

#include <stdio.h>
#include <pce.h>

int main(void) {
	static uint16_t color;

	while(1) {
		*IO_VCE_COLOR_INDEX = 0x100;
		*IO_VCE_COLOR_DATA = color++;
	}
}
