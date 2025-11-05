#include "bios.h"
#include <peekpoke.h>

void __UPLOAD_OBJECT(void) __attribute__((leaf));

void fds_bios_UploadObject(struct fds_bios_object *obj) {
  POKEW(0x00, (unsigned int)obj);
  __UPLOAD_OBJECT();
}
