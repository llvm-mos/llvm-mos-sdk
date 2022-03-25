# crt0.o is the minimal startup functionality that must be included in any C
# binary. Anything that could be provided more than one wah should be in the
# derived platform's libcrt0.
llvm_mos_sdk_add_object_file(crt0o crt0.S crt0.o)

# libcrt0 is a collection of initialization and finalization routines that may
# or may not be needed by a given program.
llvm_mos_sdk_add_library(crt0
  init-array.c
  fini-array.c
)
target_compile_options(common-crt0 PRIVATE -fno-lto)

# Exit by returning from _start.
llvm_mos_sdk_add_library(exit-return
  _exit.S
  exit-return.c
  exit.c
)
target_compile_options(common-exit-return PRIVATE -fno-lto)

# Exit by calling a platform-provided _exit.
llvm_mos_sdk_add_library(exit-custom
  exit-custom.S
  exit.c
)
target_compile_options(common-exit-custom PRIVATE -fno-lto)

# Exit by entering an infinite loop.
llvm_mos_sdk_add_library(exit-loop
  exit-custom.S
  exit-loop.c
  exit.c
)

# Zero out the BSS segment.
llvm_mos_sdk_add_library(zero-bss
  zero-bss.c
)
target_compile_options(common-zero-bss PRIVATE -fno-lto)

# Copy the data segment from its load address (LMA) to it's runtime address
# (VMA).
llvm_mos_sdk_add_library(copy-data
  copy-data.c
)
target_compile_options(common-copy-data PRIVATE -fno-lto)

# Initialize the soft stack pointer to __stack.
llvm_mos_sdk_add_library(init-stack
  init-stack.S
)

# libcrt is the libcalls needed by the compiler. All libcalls emitted by the
# compiler (except C standard library functions) should be here.
llvm_mos_sdk_add_library(crt
  const.S

  call-indir.S

  divmod.cc
  divmod-large.cc
  mul.cc
  shift.cc
)
# Don't pull in stack pointer init unnecessarily.
set_property(
  SOURCE divmod-large.cc
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
