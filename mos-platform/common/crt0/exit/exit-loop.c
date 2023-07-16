// An infinite loop is a fairly poor way of implementing _exit, but it's the
// best available default. Make this weak so users can provide a better
// application-specific implementation.
__attribute((weak)) void _exit(int status) {
  while (1)
    ;
}
__attribute__((weak, alias("_exit"))) void _Exit(int status);
