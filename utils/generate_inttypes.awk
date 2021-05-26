function pri_n(c, n, repr) {
  name = "PRI" c n
  print "#define " name " \"" repr c "\"";
  print "#define PRI" c "LEAST" n " " name;
  print "#define PRI" c "FAST" n " " name;
}

function pri(c) {
  pri_n(c, 8, "hh")
  pri_n(c, 16, "")
  pri_n(c, 32, "l")
  pri_n(c, 64, "ll")
  print "#define PRI" c "MAX PRI" c "64";
  print "#define PRI" c "PTR PRI" c "16";
  print;
}

BEGIN {
  pri("d")
  pri("i")
  pri("o")
  pri("u")
  pri("x")
  pri("X")
}
