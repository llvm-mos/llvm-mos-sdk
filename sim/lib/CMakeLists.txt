include(AddObjectFile)

add_library(sim_crt STATIC $<TARGET_OBJECTS:common_crt>)
set_target_properties(sim_crt PROPERTIES OUTPUT_NAME crt)

add_library(sim_c STATIC
   $<TARGET_OBJECTS:common_c>
   putchar.c)
set_target_properties(sim_c PROPERTIES OUTPUT_NAME c)
