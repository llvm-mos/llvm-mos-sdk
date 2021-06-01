include(AddObjectFile)
include(CompileForMOS)

compile_for_mos()

add_library(common_crt OBJECT
   const.s
   tmp.s

   call_indir.s

   divmod.c
   mul.cc
   shift.cc
)

add_library(common_c OBJECT
   # stdio.h
   printf.c

   # string.h
   mem.c
   string.c
)

add_library(m STATIC stub.c)

# Prevent the implementation of memset from being reduced to a call of memset.
set_property(SOURCE mem.c PROPERTY COMPILE_FLAGS
    -fno-builtin-memset)

set_property(SOURCE printf.c PROPERTY COMPILE_DEFINITIONS
    PRINTF_DISABLE_SUPPORT_FLOAT
    PRINTF_DISABLE_SUPPORT_EXPONENTIAL
    PRINTF_DISABLE_SUPPORT_LONG_LONG)
