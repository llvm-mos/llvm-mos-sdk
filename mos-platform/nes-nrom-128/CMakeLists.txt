platform(nes-nrom-128 PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  add_platform_examples(nes-nrom-128-examples)
  return()
endif()

install(FILES ppu.h TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_object_file(nes-nrom-128-crt0-o crt0.o crt0.c)
merge_libraries(nes-nrom-128-crt0-o common-crt0-o)

add_platform_library(nes-nrom-128-c
  ppu.c
  ppu.s
)
merge_libraries(nes-nrom-128-c common-c)
target_include_directories(nes-nrom-128-c SYSTEM BEFORE PUBLIC .)
