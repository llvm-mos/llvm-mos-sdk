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
}
