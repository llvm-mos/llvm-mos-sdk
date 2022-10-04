platform(nes-mmc1 COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  _prg-rom-fixed.ld
  common.ld
  c-in-prg-ram-0.ld
  prg-rom-16.ld
  prg-rom-32.ld
  prg-rom-32-banked.ld
  prg-rom-64.ld
  prg-rom-128.ld
  prg-rom-256.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-mmc1-crt0-o crt0.o ines.s)
add_platform_object_file(nes-mmc1-reset-o reset.o reset.s)
add_platform_object_file(nes-mmc1-init-prg-rom-32-banked-o
  init-prg-rom-32-banked.o
  init-prg-rom-32-banked.s)
add_platform_object_file(nes-mmc1-init-prg-ram-0-o
  init-prg-ram-0.o init-prg-ram-0.s)

add_platform_library(nes-mmc1-c bank.c)
merge_libraries(nes-mmc1-c common-c)
