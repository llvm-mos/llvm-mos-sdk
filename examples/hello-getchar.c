#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
  static char last_input_line[81];
  uint8_t in_end = 0;

  static const char * EXIT_TOKEN = "SOME INPUT";
  const unsigned char EXIT_TOKEN_LEN = strlen(EXIT_TOKEN);
  char eof = 0;

  while (!eof) {
    puts("ENTER SOME INPUT:");
    putchar('>'); putchar(' ');
    in_end = 0;

    for (;;) {
      const int input = getchar();
      if (input == EOF) {
        eof = 1;
        break;
      }

      putchar(input);

      if (input == '\n' ) {
        break;
      }
      last_input_line[in_end++] = input;

      // null terminate at the end of the buffer
      last_input_line[in_end] = 0;

      // exit loop before the last byte is used in the buffer. Reserve the last
      // byte for null termination.
      if (in_end == sizeof(last_input_line) - 1) {
        break;
      }
    }

    if (in_end >= EXIT_TOKEN_LEN && strncmp(EXIT_TOKEN, last_input_line, EXIT_TOKEN_LEN) == 0) {
      break;
    }
  }
  return 0;
}
