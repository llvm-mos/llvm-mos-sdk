platform(nes-gtrom COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  common.ld
  prg-rom.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-gtrom-crt0-o crt0.o ines.s)
add_platform_object_file(nes-gtrom-reset-o reset.o reset.s)

add_platform_library(nes-gtrom-c bank.c bank.s)
target_include_directories(nes-gtrom-c SYSTEM BEFORE PUBLIC ../nes/rompoke)
target_link_libraries(nes-gtrom-c PRIVATE common-asminc)
