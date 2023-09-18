
platform(nes-mmc3 COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _prg-rom-banked.ld
  _reset.ld
  c-in-prg-ram.ld
  common.ld
  prg-rom-banked-8.ld
  prg-rom-banked-mode-0.ld
  prg-rom-banked-mode-1.ld
  prg-rom-fixed.ld
TYPE LIB)
install(FILES bank.h TYPE INCLUDE)

add_platform_object_file(nes-mmc3-crt0-o crt0.o ines.s)
add_platform_object_file(nes-mmc3-reset-fixed-o reset-fixed.o reset-fixed.s)
add_platform_object_file(nes-mmc3-reset-banked-8-o reset-banked-8.o reset-banked-8.s)
add_platform_object_file(nes-mmc3-reset-banked-mode-0-o reset-banked-mode-0.o reset-banked-mode-0.s)
add_platform_object_file(nes-mmc3-reset-banked-mode-1-o reset-banked-mode-1.o reset-banked-mode-1.s)
add_platform_object_file(nes-mmc3-init-c-in-prg-ram-o init-c-in-prg-ram.o init-c-in-prg-ram.s)

add_platform_library(nes-mmc3-c bank.c bank.s irq.c irq.s)
target_include_directories(nes-mmc3-c PRIVATE ../nes)
target_link_libraries(nes-mmc3-c PRIVATE common-asminc)
