// Minimal putchar stub for LLVM-Mos
// This provides the __putchar function that sprintf requires internally
int __putchar(int c) {
    // Do nothing - this is just a stub to satisfy the linker
    // Potentially write to no$snes debug port and use a lua script for mesen
    return c;
}
