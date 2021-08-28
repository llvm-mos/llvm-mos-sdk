include(AddObjectFile)
include(CompileForMOS)

include_directories(../include)

compile_for_mos()

add_object_file(sim_crt0 crt0.s crt0)

add_library(sim_crt STATIC $<TARGET_OBJECTS:common_crt>)
set_target_properties(sim_crt PROPERTIES OUTPUT_NAME crt)

add_library(sim_c STATIC
   $<TARGET_OBJECTS:common_c>
   assert.c
   putchar.c
   stdlib.c
)
set_target_properties(sim_c PROPERTIES OUTPUT_NAME c)
