# Optionally takes an additional output name.
function(add_object_file name src)

if (ARGC GREATER 2)
  set(outname ${ARGV2})
else()
  set(outname ${name})
endif()

add_library(${name} OBJECT ${src})
add_custom_target("${name}_copy" ALL
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_OBJECTS:${name}>
            ${CMAKE_CURRENT_BINARY_DIR}/${outname}.o
    DEPENDS ${name})

endfunction()
