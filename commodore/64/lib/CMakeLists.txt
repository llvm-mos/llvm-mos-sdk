function(add_object_file name src)
add_library(${name} OBJECT ${src})
add_custom_target("${name}_copy" ALL
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_OBJECTS:${name}>
            ${CMAKE_CURRENT_BINARY_DIR}/${name}.o
    DEPENDS ${name})
endfunction()

add_object_file(basic_header basic_header.s)
add_object_file(crt0 crt0.s)

add_library(os STATIC chrout.c)
