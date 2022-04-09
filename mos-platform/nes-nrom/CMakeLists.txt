platform(nes-nrom PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES ppu.h TYPE INCLUDE)
install(FILES
  ppu.h
  nes-nrom.ld
  ines-header.ld
  ines-flags.ld
TYPE LIB)

add_platform_object_file(nes-nrom-crt0-o crt0.o
  crt0.c
  ines.s
)
merge_libraries(nes-nrom-crt0-o common-crt0-o)

add_platform_library(nes-nrom-crt0)
merge_libraries(nes-nrom-crt0
  common-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(nes-nrom-c
  ppu.c
  ppu.s
)
merge_libraries(nes-nrom-c common-c)
target_include_directories(nes-nrom-c SYSTEM BEFORE PUBLIC .)
