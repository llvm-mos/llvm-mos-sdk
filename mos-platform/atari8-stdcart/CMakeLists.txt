# TODO; refactor atari8, remove copy-data.c
platform(atari8-stdcart COMPLETE PARENT atari8)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cart-rom-fixed.ld
  link.ld
  stdcart.ld
TYPE LIB)

add_platform_library(atari8-stdcart-crt0 syms.s copy-data.c)
target_compile_options(atari8-stdcart-crt0 PRIVATE -fno-lto)
