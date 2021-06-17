include(AddObjectFile)
include(CompileForMOS)

compile_for_mos()

add_library(common_crt OBJECT
   const.s
   tmp.s
   zero_bss.c

   call_indir.s

   divmod.cc
   mul.cc
   shift.cc
)

add_library(common_c OBJECT
   # ctype.h
   ctype.c

   # stdio.h
   printf.c

   # stdlib.h
   abs.cc

   # string.h
   mem.c
   string.c
)

add_library(m STATIC stub.c)

# Prevent the implementation of libcalls from being reduced to a call of those libcalls.
set_property(SOURCE mem.c PROPERTY COMPILE_FLAGS -fno-builtin-memset)

set_property(SOURCE printf.c PROPERTY COMPILE_DEFINITIONS
    PRINTF_DISABLE_SUPPORT_FLOAT
    PRINTF_DISABLE_SUPPORT_EXPONENTIAL)
