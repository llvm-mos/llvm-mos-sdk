platform(mega65 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES link.ld TYPE LIB)

add_platform_object_file(mega65-basic-header basic-header.o basic-header.S)
add_platform_object_file(mega65-unmap-basic unmap-basic.o unmap-basic.S)

add_platform_library(mega65-c kernal.S)
target_include_directories(mega65-c BEFORE PUBLIC .)
