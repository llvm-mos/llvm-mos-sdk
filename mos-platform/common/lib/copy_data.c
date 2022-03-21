#include <string.h>

extern char __data_start[];
extern char __data_end[];

extern char __data_load_start[];

void __copy_data(void) {
  memcpy(__data_start, __data_load_start, __data_end - __data_start);
}
