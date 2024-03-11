#include <stdio.h>

// Default signal handlers, sans the final _Exit. These may be overridden by
// defaults in derived targets, usually due to character set differences. These
// need to be in a separate file from signal.c to ensure that the
// override copies are extracted.

__attribute((weak)) void __sigabrt(void) { fputs("Aborted\n", stderr); }
__attribute((weak)) void __sigfpe(void) {
  fputs("Fatal arithmetic error\n", stderr);
}
__attribute((weak)) void __sigill(void) {
  fputs("Illegal instruction\n", stderr);
}
__attribute((weak)) void __sigint(void) { fputs("Interrupted\n", stderr); }
__attribute((weak)) void __sigsegv(void) {
  fputs("Segmentation fault\n", stderr);
}
__attribute((weak)) void __sigterm(void) {}
