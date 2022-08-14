platform(nes-mmc1 COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  c-in-prg-ram.ld
  c-in-ram.ld
  common.ld
  prg-rom-mode-0.ld
  prg-rom-mode-2.ld
  prg-rom-mode-3.ld
TYPE LIB)

add_platform_object_file(nes-mmc1-crt0-o crt0.o ines.s)
