install(FILES neslib.h TYPE INCLUDE)

add_library(nes-neslib-asminc INTERFACE)
target_include_directories(nes-neslib-asminc INTERFACE .)

add_platform_library(nes-neslib
  neslib.c
  neslib.s
  ntsc.c
  ntsc.s
  rand.c
  rand.s)
target_include_directories(nes-neslib BEFORE PUBLIC ..)
target_link_libraries(nes-neslib PRIVATE common-asminc nes-neslib-asminc)
