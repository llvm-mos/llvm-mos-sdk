#include <unistd.h>

// stdin, stdout, stderr, CON: and TTY: are descriptors 0 to 4, all the console.
int isatty(int fd) { return (unsigned)fd < 5; }
