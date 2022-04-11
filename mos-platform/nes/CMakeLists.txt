platform(nes PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES ppu.h TYPE INCLUDE)
install(FILES
  ppu.h
  ines-header.ld
  nes-imag-regs.ld
TYPE LIB)

add_platform_object_file(nes-crt0-o crt0.o
  crt0.c
)
merge_libraries(nes-crt0-o common-crt0-o)

add_platform_library(nes-crt0)
merge_libraries(nes-crt0
  common-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(nes-c
  ppu.c
  ppu.s
)
merge_libraries(nes-c common-c)
target_include_directories(nes-c SYSTEM BEFORE PUBLIC .)
