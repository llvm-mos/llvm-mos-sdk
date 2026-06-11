#include <stdio.h>
#include <unistd.h>

/* unlink() is the same as remove() on the RP6502
 * (UNLINK removes a file or an empty directory). */
int unlink(const char *name) { return remove(name); }
