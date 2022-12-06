platform(atari8-stdcart COMPLETE PARENT atari8)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cart-rom-fixed.ld
  c-in-ram.ld
  common.ld
  link.ld
  stdcart.ld
TYPE LIB)

add_platform_object_file(atari8-stdcart-crt0-o crt0.o syms.s)
