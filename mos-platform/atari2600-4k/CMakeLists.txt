platform(atari2600-4k COMPLETE PARENT atari2600-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  mapper.h
TYPE INCLUDE)

install(FILES
  link.ld
TYPE LIB)

