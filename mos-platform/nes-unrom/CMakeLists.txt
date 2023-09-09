platform(nes-unrom COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  common.ld
  prg-rom.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-unrom-crt0-o crt0.o ines.s)
add_platform_object_file(nes-unrom-reset-o reset.o reset.s)

add_platform_library(nes-unrom-c bank.c bank.s)
target_link_libraries(nes-unrom-c PRIVATE common-asminc)
