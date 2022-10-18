install(FILES famitone2.h TYPE INCLUDE)

add_platform_library(nes-famitone2
  famitone2.s
  famitone2.c
  music_bank.c
  music_bank.s
  sounds_bank.c
  sounds_bank.s
)
target_include_directories(nes-famitone2 PRIVATE .)
