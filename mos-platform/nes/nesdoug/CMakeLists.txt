install(FILES nesdoug.h TYPE INCLUDE)

add_platform_library(nes-nesdoug nesdoug.s nesdoug.c)
target_include_directories(nes-nesdoug BEFORE PUBLIC ..)
