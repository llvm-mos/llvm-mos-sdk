#include <peekpoke.h>

char __CHECK_DISK_HEADER(void) __attribute__((leaf));

char fds_bios_CheckDiskHeader(char string[10]) {
  POKEW(0x00, (unsigned int)string);
  return __CHECK_DISK_HEADER();
}
