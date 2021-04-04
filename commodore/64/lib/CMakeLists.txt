include(AddObjectFile)

add_object_file(basic_header basic_header.s)
add_object_file(crt0 crt0.s)

add_library(c64_os STATIC chrout.c $<TARGET_OBJECTS:common_os>)
set_target_properties(c64_os PROPERTIES OUTPUT_NAME os)
