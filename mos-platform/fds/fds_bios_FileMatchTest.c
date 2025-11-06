#include <peekpoke.h>

void __FILE_MATCH_TEST(void) __attribute__((leaf));

char fds_bios_FileMatchTest(char *ids) {
  POKEW(0x02, (unsigned int)ids);
  __FILE_MATCH_TEST();
  return PEEK(0x09);
}
