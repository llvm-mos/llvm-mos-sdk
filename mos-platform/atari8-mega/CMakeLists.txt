platform(atari8-mega COMPLETE PARENT atari8-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES link.ld TYPE LIB)

add_platform_library(atari8-mega-crt0 syms.s)
merge_libraries(atari8-mega-crt0
  common-copy-data
  common-zero-bss
  common-exit-loop
)
target_link_libraries(atari8-mega-crt0 PRIVATE common-asminc)
