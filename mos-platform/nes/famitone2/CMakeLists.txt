install(FILES famitone2.h TYPE INCLUDE)

add_platform_library(nes-famitone2
  famitone2.s
  famitone2.c
  init.s
)
target_include_directories(nes-famitone2 PRIVATE .)
