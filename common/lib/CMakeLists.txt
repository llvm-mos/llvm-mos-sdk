include(AddObjectFile)

add_object_file(crt0 crt0.s)

add_library(common_crt OBJECT call_indir.s tmp.s)

add_library(common_c OBJECT printf.c)
set_property(SOURCE printf.c PROPERTY COMPILE_DEFINITIONS
    PRINTF_DISABLE_SUPPORT_FLOAT
    PRINTF_DISABLE_SUPPORT_EXPONENTIAL
    PRINTF_DISABLE_SUPPORT_LONG_LONG)
