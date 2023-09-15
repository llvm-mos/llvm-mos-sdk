platform(nes-cnrom COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
_rompoke.ld
  common.ld
  c-in-prg-ram.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-cnrom-crt0-o crt0.o ines.s)

add_platform_library(nes-cnrom-c bank.c)
target_include_directories(nes-cnrom-c PRIVATE ../nes)
target_include_directories(nes-cnrom-c SYSTEM BEFORE PUBLIC ../nes/rompoke)
target_link_libraries(nes-cnrom-c PRIVATE common-asminc)
