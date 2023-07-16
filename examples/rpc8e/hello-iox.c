/**
 * hello-iox
 *
 * To the extent possible under law, the person who associated CC0 with
 * hello-iox has waived all copyright and related or neighboring rights
 * to hello-iox.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <rpc8e.h>
#include <stdio.h>

// The IO Expander is a Bundled Cable input/output device.

#define IO_EXPANDER_ID 3

void putstr(const char *s) {
  for (; *s; ++s)
    __putchar(*s);
}

int main(void) {
  uint16_t curr_input;
  uint16_t next_input = 0;

  rpc8e_display_clear();
  putstr("IO Expander Demo\n\n");

  // Map the I/O expander.
  uint8_t old_device = rpc8e_redbus_map(IO_EXPANDER_ID);

  // Reset the I/O expander's output.
  *IO_IOX_OUTPUT = 0;

  // Unmap the I/O expander.
  rpc8e_redbus_set_map(old_device);

  // Main loop.
  while (true) {
    curr_input = next_input;
    putstr("Active Colors");
    if (curr_input & COLOR_WHITE)
      putstr(", White");
    if (curr_input & COLOR_ORANGE)
      putstr(", Orange");
    if (curr_input & COLOR_MAGENTA)
      putstr(", Magenta");
    if (curr_input & COLOR_LIGHT_BLUE)
      putstr(", Light Blue");
    if (curr_input & COLOR_YELLOW)
      putstr(", Yellow");
    if (curr_input & COLOR_LIME)
      putstr(", Lime");
    if (curr_input & COLOR_PINK)
      putstr(", Pink");
    if (curr_input & COLOR_GRAY)
      putstr(", Gray");
    if (curr_input & COLOR_LIGHT_GRAY)
      putstr(", Light Gray");
    if (curr_input & COLOR_CYAN)
      putstr(", Cyan");
    if (curr_input & COLOR_PURPLE)
      putstr(", Purple");
    if (curr_input & COLOR_BLUE)
      putstr(", Blue");
    if (curr_input & COLOR_BROWN)
      putstr(", Brown");
    if (curr_input & COLOR_GREEN)
      putstr(", Green");
    if (curr_input & COLOR_RED)
      putstr(", Red");
    if (curr_input & COLOR_BLACK)
      putstr(", Black");
    putstr("\n");

    // Map the I/O expander.
    old_device = rpc8e_redbus_map(IO_EXPANDER_ID);

    // Wait for a state change.
    while (curr_input == next_input) {
      rpc8e_cpu_wait();
      next_input = *IO_IOX_INPUT;
    }

    // Unmap the I/O expander.
    rpc8e_redbus_set_map(old_device);
  }

  return 0;
}
