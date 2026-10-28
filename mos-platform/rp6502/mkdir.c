#include <rp6502.h>
#include <unistd.h>

int mkdir(const char *name, ...) { return f_mkdir(name); }
