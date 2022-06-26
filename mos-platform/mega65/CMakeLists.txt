platform(mega65 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES link.ld TYPE LIB)

add_platform_object_file(mega65-basic-header basic-header.o basic-header.S)

