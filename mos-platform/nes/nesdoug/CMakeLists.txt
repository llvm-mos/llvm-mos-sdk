install(FILES
  nesdoug.h
  padlib.h
  zaplib.h
TYPE INCLUDE)

add_platform_library(nes-nesdoug
  nesdoug.s
  nesdoug.c
  padlib.s
  zaplib.s
)
target_include_directories(nes-nesdoug BEFORE PUBLIC ..)
