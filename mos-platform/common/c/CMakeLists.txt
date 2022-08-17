# C standard library and C++ abi.
add_platform_library(common-c
  # ctype.h
  ctype.c

  # setjmp.h
  setjmp.S

  # stdio.h
  printf.c
  stdio.c

  # stdlib.h
  abs.cc
  stdlib.cc
  new.cc

  # string.h
  mem.c
  string.c

  # exception
  exception.cc

  # Itanium ABI implementation
  cxa-abi.cc
  cxa-atexit.cc
  private-typeinfo.cc
)
# Prevent the implementation of libcalls from being reduced to a call of those libcalls.
set_property(SOURCE mem.c PROPERTY COMPILE_OPTIONS -fno-builtin-memset)
set_property(SOURCE printf.c PROPERTY COMPILE_DEFINITIONS
  PRINTF_DISABLE_SUPPORT_FLOAT
  PRINTF_DISABLE_SUPPORT_EXPONENTIAL
)
target_include_directories(common-c SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})