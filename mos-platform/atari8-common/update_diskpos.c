#include <stdio.h>
#include <__stdio-internal.h>

char __note(int fd, fpos_t *pos);

void __update_diskpos(FILE *stream) {
  __note(stream->handle, &stream->diskpos);
}
