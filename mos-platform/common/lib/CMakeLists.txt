# libstart is a collection of initialization and finalization routines that may
# or may not be needed by a given program. These are basically the optional
# portions of crt0.o.
llvm_mos_sdk_add_library(start
  zero_bss.c

  init_array.c
  fini_array.c

  exit_return.c
)
target_compile_options(common-start PRIVATE -fno-lto)

# libcrt is the libcalls needed by the compiler. All libcalls emitted by the
# compiler (except C standard library functions) should be here.
llvm_mos_sdk_add_library(crt
  const.S

  call_indir.S

  divmod.cc
  divmod_large.cc
  mul.cc
  shift.cc
)
# Don't pull in stack pointer init unnecessarily.
set_property(
  SOURCE divmod_large.cc
  PROPERTY COMPILE_FLAGS -fno-lto
)

# C standard library and C++ abi.
llvm_mos_sdk_add_library(c
  # ctype.h
  ctype.c

  # setjmp.h
  setjmp.S

  # stdio.h
  printf.c
  stdio.c

  # stdlib.h
  abs.cc
  exit.c
  stdlib.cc
  new.cc

  # string.h
  mem.c
  string.c

  # exception
  exception.cc

  # Itanium ABI implementation
  cxa_abi.cc
  cxa_atexit.cc
  private_typeinfo.cpp
)
# Prevent the implementation of libcalls from being reduced to a call of those libcalls.
set_property(
  SOURCE mem.c
  PROPERTY COMPILE_FLAGS -fno-builtin-memset
)
set_property(
  SOURCE printf.c
  PROPERTY COMPILE_DEFINITIONS
  PRINTF_DISABLE_SUPPORT_FLOAT
  PRINTF_DISABLE_SUPPORT_EXPONENTIAL
)

# Math library; just a stub for now.
llvm_mos_sdk_add_library(m)
