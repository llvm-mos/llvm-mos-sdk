platform(cx16 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES _6522.h cx16.h TYPE INCLUDE)
install(FILES imag-regs.ld link.ld TYPE LIB)

add_platform_object_file(cx16-basic-header basic-header.o basic-header.S)

add_platform_library(cx16-c kernal.S)
target_include_directories(cx16-c BEFORE PUBLIC .)

