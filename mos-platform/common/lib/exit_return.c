
__attribute__((leaf)) void _fini(void);

// Runs finalizers, then returns to the calleer. Jumping to here after main has
// the effect of returning from _start with the given status. When applicable,
// this can be more efficient than using non-local jump machinery to perform a
// general _exit.
char __exit_return(int status) {
  _fini();
  return (char)status;
}
