void __sim_exit(int status) {
  // Writing to this IO register causes the simulator to exit with the given status.
  (*(volatile char *)0xFFF8) = (char)status;

  // Prevent the compiler from considering this entire basic block unreachable.
  asm volatile ("");

  __builtin_unreachable();
}