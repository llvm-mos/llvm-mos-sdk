install(FILES neslib.h TYPE INCLUDE)

add_platform_library(nes-neslib
  neslib.c
  neslib.s
  ntsc.c
  ntsc.s
  rand.c
  rand.s)
target_include_directories(nes-neslib BEFORE PUBLIC ..)
