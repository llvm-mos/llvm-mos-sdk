install(FILES neslib.h TYPE INCLUDE)

add_platform_library(nes-neslib neslib.s neslib.c)
target_include_directories(nes-neslib BEFORE PUBLIC ..)
