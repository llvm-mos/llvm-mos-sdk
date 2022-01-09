# AWK script to generate the contents of this directory.

BEGIN {
  print "# GENERATED FILE -- DO NOT MANUALLY EDIT" > "CMakeLists.txt";
  print "llvm_mos_sdk_install(FILES" > "CMakeLists.txt";
  for (i = 0; i < 256; i++) {
    file = i ".ld"
    print "/* GENERATED FILE -- DO NOT MANUALLY EDIT. */" > file;
    if (i == 0)
      print "PROVIDE(__rc0 = 0);" > file;
    else {
      printf "INCLUDE imag_reg/%s.ld\n", i - 1 > file;
      printf "PROVIDE(__rc%s = __rc%s + 1);\n", i, i - 1 > file;
    }
    printf "  %s\n", file > "CMakeLists.txt";
  }
  print ")" > "CMakeLists.txt";
}
