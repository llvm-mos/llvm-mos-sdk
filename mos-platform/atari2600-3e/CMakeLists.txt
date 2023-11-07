platform(atari2600-3e COMPLETE PARENT atari2600)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

file(READ clang.cfg CONFIG)

install(FILES
  link.ld
TYPE LIB)

add_platform_library(atari2600-3e-c
  mapper_3e.c
)
target_include_directories(atari2600-3e-c SYSTEM BEFORE PUBLIC .)
