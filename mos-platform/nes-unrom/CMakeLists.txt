platform(nes-unrom COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  _rompoke.ld
  common.ld
  prg-rom.ld
TYPE LIB)
install(FILES mapper.h TYPE INCLUDE)

add_platform_object_file(nes-unrom-crt0-o crt0.o ines.s)
add_platform_object_file(nes-unrom-reset-o reset.o reset.s)

add_platform_library(nes-unrom-c mapper.c mapper.s)
target_include_directories(nes-unrom-c PRIVATE ../nes)
target_include_directories(nes-unrom-c PRIVATE ../nes/rompoke)
target_link_libraries(nes-unrom-c PRIVATE common-asminc)
