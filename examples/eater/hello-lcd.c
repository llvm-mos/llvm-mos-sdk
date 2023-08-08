// Example that scrolls a message across the 16x2 LCD screen.

#include <eater.h>

// maximum message size for marquee: 16 characters
static const char message[] = "Hello, World!";
#define message_len (sizeof(message) - 1)

int main(void) {
  // initialize and clear the LCD display
  lcd_init();

  // write the message to just off-screen
  lcd_instruction(LCD_I_DDRAM | 16);
  lcd_puts(message);

  // scroll the message across the screen
  int count = 16 + message_len;
  int x = count;
  for (;;) {
    // wait before scrolling the screen again
    delay(350);

    if (x <= 0) {
      // reset the scroll
      lcd_instruction(LCD_I_HOME);
      x = count;
    } else {
      // shift the display left one position
      lcd_instruction(LCD_I_SHIFT_L);
      --x;
    }
  }
  return 0;
}
