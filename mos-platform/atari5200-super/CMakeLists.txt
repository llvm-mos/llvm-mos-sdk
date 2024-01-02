
platform(atari5200-super HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES link.ld TYPE LIB)

add_platform_library(atari5200-super-crt0)
target_link_libraries(atari5200-super-crt0 PRIVATE common-asminc)

merge_libraries(atari5200-super-crt0
  common-init-stack
  common-copy-data
  common-zero-bss
  common-exit-loop
)
target_link_libraries(atari5200-super-crt0 PRIVATE common-asminc)
