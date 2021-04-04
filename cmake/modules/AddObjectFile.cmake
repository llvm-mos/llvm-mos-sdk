function(add_object_file name src)
add_library(${name} OBJECT ${src})
add_custom_target("${name}_copy" ALL
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_OBJECTS:${name}>
            ${CMAKE_CURRENT_BINARY_DIR}/${name}.o
    DEPENDS ${name})
endfunction()
