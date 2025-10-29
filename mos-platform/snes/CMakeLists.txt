platform(snes COMPLETE PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

add_platform_library(snes-crt0)
merge_libraries(snes-crt0
  common-init-stack
  common-copy-zp-data
  common-copy-data
  common-zero-bss
)

add_platform_library(snes-c
  putchar_stub.c
  startup.s
  vectors.s
)

add_subdirectory(snesxc)
target_include_directories(snes-c SYSTEM BEFORE PUBLIC .)
