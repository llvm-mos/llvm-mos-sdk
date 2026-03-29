#include "rp6502.h"
#include <stddef.h>
#include <stdint.h>

int __argc;
char **__argv;

/* Override to provide storage for argv, e.g.:
 *   void *argv_mem(size_t size) { return malloc(size); }
 * Returns NULL (default) to silently skip argc/argv setup.
 */
__attribute__((weak)) void *argv_mem(size_t size) {
  (void)size;
  return NULL;
}

/* .init.220: after zero-bss (.init.200) so malloc is usable in argv_mem(). */
asm(".section .init.220,\"ax\",@progbits\n"
    "  jsr __do_initmainargs\n");

void __do_initmainargs(void) {
  int size = ria_call_int(RIA_OP_ARGV);
  if (size <= 0)
    return;

  void *buf = argv_mem((size_t)(unsigned int)size);
  if (!buf) {
    ria_call_int(RIA_OP_ZXSTACK); /* discard pending xstack data */
    return;
  }

  /* Pop all bytes from xstack into buf, in order. */
  unsigned char *p = (unsigned char *)buf;
  unsigned int n = (unsigned int)size;
  while (n--)
    *p++ = ria_pop_char();

  /* Relocate the offset table at the head of buf.
   * The RIA stores 2-byte little-endian offsets relative to buf start.
   * A zero entry terminates the table. */
  unsigned char *raw = (unsigned char *)buf;
  char **ptrs = (char **)buf;
  int argc = 0;
  for (;;) {
    uint16_t offset =
        (uint16_t)raw[argc * 2] | ((uint16_t)raw[argc * 2 + 1] << 8);
    if (!offset) {
      ptrs[argc] = NULL;
      break;
    }
    ptrs[argc] = (char *)buf + offset;
    argc++;
  }
  __argc = argc;
  __argv = ptrs;
}
