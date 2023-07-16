asm(".global __after_main\n"
    ".section .after_main,\"axR\",@progbits\n"
    "__after_main:\n"
    "  jmp __exit_return\n");

__attribute__((leaf)) void _fini(void);

// Runs finalizers, then returns to the caller. Jumping to here after main has
// the effect of returning from _start with the given status. When applicable,
// this can be more efficient than using non-local jump machinery to perform a
// general _exit.
char __exit_return(int status) {
  _fini();
  return (char)status;
}
