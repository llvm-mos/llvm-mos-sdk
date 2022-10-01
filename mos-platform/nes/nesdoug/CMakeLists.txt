install(FILES
  nesdoug.h
  zaplib.h
TYPE INCLUDE)

add_platform_library(nes-nesdoug
  nesdoug.s
  nesdoug.c
  zaplib.s
)
target_include_directories(nes-nesdoug BEFORE PUBLIC ..)
