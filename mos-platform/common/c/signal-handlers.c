#include <stdio.h>

// Default signal handlers, sans the final _Exit. These may be overridden by
// defaults in derived targets, usually due to character set differences. These
// need to be in a separate file from signal.c to ensure that the
// override copies are extracted.

__attribute((weak)) void __sigabrt(void) { puts("Aborted"); }
__attribute((weak)) void __sigfpe(void) { puts("Fatal arithmetic error"); }
__attribute((weak)) void __sigill(void) { puts("Illegal instruction"); }
__attribute((weak)) void __sigint(void) { puts("Interrupted"); }
__attribute((weak)) void __sigsegv(void) { puts("Segmentation fault"); }
__attribute((weak)) void __sigterm(void) {}
