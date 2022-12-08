platform(atari8-stdcart COMPLETE PARENT atari8)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cart-rom-fixed.ld
  link.ld
  stdcart.ld
TYPE LIB)

# do not create crt0, that will take precedence over common/lib/crt0.o
# which we depend on
add_platform_library(atari8-stdcart-c
  syms.s)
merge_libraries(atari8-stdcart-c
  common-c)
