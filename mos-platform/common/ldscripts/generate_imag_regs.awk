# AWK script to generate the contents of this directory.

BEGIN {
  file = "imag-regs.ld"
  print "/* GENERATED FILE -- DO NOT MANUALLY EDIT. */" > file;
  print "/* Note: The odd regs must immediately follow the even regs" > file;
  print " * for even/odd pairs to work as pointers, but the even regs" > file;
  print " * can be assigned arbitrarily in linker scripts.*/" > file;
  for (i = 1; i < 32; i++) {
    # The odd regs must immediately follow the even regs to be used as pointers,
    # but the even regs are unconstrained.
    if (i % 2 == 0)
      printf "PROVIDE(" > file;
    printf "__rc%s = __rc%s + 1", i, i - 1 > file;
    if (i % 2 == 0)
      printf ")" > file
    printf ";\n" > file
  }

  # Emit a template linker-script fragment for custom ISR register suffixes.
  # Users copy this, replace SFX with their suffix, and pass it as an extra
  # linker input (-T) to place the registers at fixed addresses.
  file = "imag-regs-suffix-template.ld"
  print "/* GENERATED FILE -- DO NOT MANUALLY EDIT. */" > file;
  print "/* Copy this file, replace SFX with your suffix (e.g. __nmi), and" > file;
  print " * pass it as an extra linker script (-T my-isr-regs.ld). The even regs" > file;
  print " * can be assigned arbitrarily; the odd regs must immediately follow." > file;
  print " */" > file;
  for (i = 0; i < 32; i += 2) {
    # Even reg: user fills in the address.
    printf "/* __rc%sSFX = 0x00XX; */\n", i > file;
    # Odd reg: immediately follows the even reg.
    printf "__rc%sSFX = __rc%sSFX + 1;\n", i + 1, i > file;
  }
}
