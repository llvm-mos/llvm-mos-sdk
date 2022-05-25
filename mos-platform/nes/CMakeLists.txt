platform(nes PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES ppu.h TYPE INCLUDE)
install(FILES
  ppu.h
  nes.ld
  ines.ld
  ines-header.ld
  ines-roms.ld
  nes-imag-regs.ld
  nes-ram.ld
TYPE LIB)

add_platform_object_file(nes-crt0-o crt0.o crt0.c ines.s)

add_platform_library(nes-crt0)
merge_libraries(nes-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(nes-c
  ppu.c
  ppu.s
)
target_include_directories(nes-c SYSTEM BEFORE PUBLIC .)
