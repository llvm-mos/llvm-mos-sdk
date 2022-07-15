platform(atari8 COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES chrout.h TYPE INCLUDE)

add_platform_library(atari8-crt0 init-stack.S)
merge_libraries(atari8-crt0
  common-copy-zp-data
  common-zero-bss
  common-exit-return
)

add_platform_library(atari8-c
  abort.c
  chrout.c
  putchar.c
  getchar.c
)
target_include_directories(atari8-c SYSTEM BEFORE PUBLIC .)

# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily. It can be called in an interrupt.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto -fno-static-stack)
