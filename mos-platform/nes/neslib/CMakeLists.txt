install(FILES neslib.h TYPE INCLUDE)

add_library(nes-neslib-asminc INTERFACE)
target_include_directories(nes-neslib-asminc INTERFACE .)

add_platform_library(nes-neslib
  neslib.c
  neslib.s
  ntsc.c
  ntsc.s
  oam_update.c
  oam_update.s
  pal_bright.c
  pal_bright.s
  pal_update.c
  pal_update.s
  rand.c
  rand.s
  vram_update.c
  vram_update.s)
target_include_directories(nes-neslib BEFORE PUBLIC ..)
target_link_libraries(nes-neslib PRIVATE common-asminc nes-neslib-asminc)
