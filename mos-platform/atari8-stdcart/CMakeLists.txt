platform(atari8-stdcart COMPLETE PARENT atari8)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cart-rom-fixed.ld
  link.ld
  stdcart.ld
TYPE LIB)

# TODO; refactor out atari8 targets
add_platform_library(atari8-stdcart-crt0 syms.s)
merge_libraries(atari8-stdcart-crt0
  atari8-crt0
  common-copy-data
)
