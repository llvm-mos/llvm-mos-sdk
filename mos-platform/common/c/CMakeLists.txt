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

  # setjmp.h
  setjmp.S

  # signal.h
  signal.c
  signal-handlers.c

  # stdio.h
  printf.c
  stdio.c

  # stdlib.h
  abs.cc
  atoi.cc
  div.cc
  stdlib.c
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
)
# Prevent the implementation of libcalls from being reduced to a call of those libcalls.
set_property(SOURCE mem.c PROPERTY COMPILE_OPTIONS -fno-builtin-memset)
set_property(TARGET common-c PROPERTY COMPILE_DEFINITIONS
  PRINTF_DISABLE_SUPPORT_FLOAT
  PRINTF_DISABLE_SUPPORT_EXPONENTIAL
  PRINTF_WEAK
)
target_include_directories(common-c SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})
target_link_libraries(common-c PRIVATE common-asminc)

add_platform_library(common-printf_flt printf.c)
target_include_directories(common-printf_flt SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})
