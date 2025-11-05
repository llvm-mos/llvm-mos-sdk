#include <peekpoke.h>

void __GET_NUM_FILES(void) __attribute__((leaf));

unsigned char fds_bios_GetNumFiles(void) {
  __GET_NUM_FILES();
  return PEEK(0x06);
}
