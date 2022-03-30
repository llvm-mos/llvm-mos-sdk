void _exit(int status) { while (1); }
__attribute__((alias("_exit"))) void _Exit(int status);
