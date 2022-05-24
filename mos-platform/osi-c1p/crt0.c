extern void __clrscr(void);

asm(
  ".section .init.40,\"axR\",@progbits\n"
  "  jsr __late_init\n"
);

void __late_init(void) {
  __clrscr();
}