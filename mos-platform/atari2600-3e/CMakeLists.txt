platform(atari2600-3e COMPLETE PARENT atari2600-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

file(READ clang.cfg CONFIG)

install(FILES
  mapper.h
TYPE INCLUDE)

install(FILES
  link.ld
TYPE LIB)

add_platform_object_file(atari2600-3e-init-mapper-o
  init_mapper_3e.o
  init_mapper_3e.S
)

add_platform_library(atari2600-3e-c
  mapper_3e.c
)
target_include_directories(atari2600-3e-c SYSTEM BEFORE PUBLIC .)
