include(AddObjectFile)

add_object_file(basic_header basic_header.s)

add_library(c64_crt STATIC $<TARGET_OBJECTS:common_crt>)
set_target_properties(c64_crt PROPERTIES OUTPUT_NAME crt)

add_library(c64_c STATIC chrout.c $<TARGET_OBJECTS:common_c>)
set_target_properties(c64_c PROPERTIES OUTPUT_NAME c)
