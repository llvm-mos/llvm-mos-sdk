add_library(c64_basic_header OBJECT c64_basic_header.s)
add_custom_target(c64_basic_header_copy ALL
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_OBJECTS:c64_basic_header>
            ${CMAKE_CURRENT_BINARY_DIR}/c64_basic_header.o
    DEPENDS c64_basic_header)

add_library(crt0 OBJECT crt0.s)
add_custom_target(crt0_copy ALL
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_OBJECTS:crt0>
            ${CMAKE_CURRENT_BINARY_DIR}/crt0.o
    DEPENDS crt0)
