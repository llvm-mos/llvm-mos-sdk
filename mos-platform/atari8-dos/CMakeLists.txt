platform(atari8-dos COMPLETE HOSTED PARENT atari8-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_library(atari8-dos-crt0)
merge_libraries(atari8-dos-crt0
  common-copy-zp-data
  common-zero-bss
  common-exit-return
)
target_link_libraries(atari8-dos-crt0 PRIVATE common-asminc)
