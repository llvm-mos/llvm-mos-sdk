platform(nes-action53 COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  common.ld
  prg-rom.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-action53-crt0-o crt0.o ines.s)
add_platform_object_file(nes-action53-reset-o reset.o reset.s)

add_platform_library(nes-action53-c bank.c bank.s)
target_include_directories(nes-action53-c PRIVATE ../nes)
target_link_libraries(nes-action53-c PRIVATE common-asminc)
