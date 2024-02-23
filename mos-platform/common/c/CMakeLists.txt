# C standard library and C++ abi.
add_platform_library(common-c
  # assert.h
  assert.c

  # ctype.h
  ctype.c

  # errno.h
  errno.c

  # inttypes.h
  inttypes.c

  # math.h
  math.cc

  # setjmp.h
  setjmp.S

  # signal.h
  signal.c
  signal-handlers.c

  # stdio.h
  char-conv.c
  printf.cc
  stdio.c

  # stdlib.h
  abs.cc
  atoi.cc
  bsearch.c
  div.cc
  stdlib.cc
  malloc.cc
  malloc.s
  new.cc
  qsort.c
  quick-exit.cc

  # string.h
  mem.c
  strerror.c
  string.c

  # exception
  exception.cc

  # Itanium ABI implementation
  atexit-impl.cc
  cxa-atexit.cc
  cxa-abi.cc
  private-typeinfo.cc

  # Internal libraries
  varint.cc

  # Provides a ungetc-aware getchar that is bigger than the one in stdio.c
  ungetc.c
)
# Prevent the implementation of libcalls from being reduced to a call of those libcalls.
set_property(SOURCE mem.c PROPERTY COMPILE_OPTIONS -fno-builtin-memset)
target_include_directories(common-c SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})
target_link_libraries(common-c PRIVATE common-asminc)

add_platform_library(common-printf_flt printf.cc)
target_include_directories(common-printf_flt SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})
set_property(TARGET common-printf_flt PROPERTY COMPILE_DEFINITIONS
  _PRINTF_FLOAT
)
