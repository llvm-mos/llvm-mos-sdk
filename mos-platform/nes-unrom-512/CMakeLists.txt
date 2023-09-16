platform(nes-unrom-512 COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  _rompoke.ld
  common.ld
  prg-rom.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-unrom-512-crt0-o crt0.o ines.s)
add_platform_object_file(nes-unrom-512-reset-o reset.o reset.s)

add_platform_library(nes-unrom-512-c bank.c bank.s)
target_include_directories(nes-unrom-512-c PRIVATE ../nes)
target_include_directories(nes-unrom-512-c PRIVATE ../nes/rompoke)
target_link_libraries(nes-unrom-512-c PRIVATE common-asminc)
