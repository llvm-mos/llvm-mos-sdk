include(AddObjectFile)
include(CompileForMOS)

compile_for_mos()

add_object_file(atari800_crt0 crt0.s crt0)

add_library(atari800_crt STATIC $<TARGET_OBJECTS:common_crt>)
set_target_properties(atari800_crt PROPERTIES OUTPUT_NAME crt)

add_library(atari800_c STATIC
   $<TARGET_OBJECTS:common_c>
   chrout.c
   putchar.c
)
set_target_properties(atari800_c PROPERTIES OUTPUT_NAME c)
