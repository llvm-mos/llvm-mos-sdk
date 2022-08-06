platform(c64 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES link.ld TYPE LIB)

install(FILES
  c64.inc
DESTINATION ${ASMINCDIR})

add_platform_object_file(c64-basic-header basic-header.o basic-header.S)

add_platform_library(c64-c kernal.S)
target_include_directories(c64-c BEFORE PUBLIC .)

