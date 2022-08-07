platform(nes PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  nes.h
  ppu.h
TYPE INCLUDE)
install(FILES
  chr-rom.ld
  ines-header.ld
  ines-roms.ld
  ines.ld
  nes.ld
TYPE LIB)
install(FILES nes.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(nes-crt0-o crt0.o crt0.c ines.s)

add_platform_library(nes-crt0)
merge_libraries(nes-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(nes-c ppu.c)
target_include_directories(nes-c SYSTEM BEFORE PUBLIC .)
