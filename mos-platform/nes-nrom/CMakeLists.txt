platform(nes-nrom COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  common.ld
  c-in-prg-ram.ld
TYPE LIB)

add_platform_object_file(nes-nrom-crt0-o crt0.o ines.s)
