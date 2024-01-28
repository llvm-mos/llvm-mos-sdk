// An infinite loop is a fairly poor way of implementing _Exit, but it's the
// best available default. Make this weak so users can provide a better
// application-specific implementation.
__attribute((weak)) void _Exit(int status) {
  while (1)
    ;
}
