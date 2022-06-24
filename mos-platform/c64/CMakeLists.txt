platform(c64 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES link.ld TYPE LIB)

add_platform_object_file(c64-basic-header basic-header.o basic-header.S)

