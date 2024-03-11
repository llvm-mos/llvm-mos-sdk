install(FILES
  nesdoug.h
  padlib.h
  zaplib.h
TYPE INCLUDE)

add_platform_library(nes-nesdoug
  metatile.c
  metatile.s
  nesdoug.s
  nesdoug.c
  padlib.s
  vram_buffer.c
  vram_buffer.s
  vram_buffer_ops.s
  zaplib.s
)
target_include_directories(nes-nesdoug BEFORE PUBLIC ..)
target_link_libraries(nes-nesdoug PRIVATE common-asminc nes-neslib-asminc)
