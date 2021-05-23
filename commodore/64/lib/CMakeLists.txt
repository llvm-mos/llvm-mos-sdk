include(AddObjectFile)
include(CompileForMOS)

compile_for_mos()

add_object_file(basic_header basic_header.s)

add_object_file(c64_crt0 crt0.s crt0)

add_library(c64_crt STATIC $<TARGET_OBJECTS:common_crt>)
set_target_properties(c64_crt PROPERTIES OUTPUT_NAME crt)

add_library(c64_c STATIC
   $<TARGET_OBJECTS:common_c>
   chrout.c
   putchar.c
)
set_target_properties(c64_c PROPERTIES OUTPUT_NAME c)
