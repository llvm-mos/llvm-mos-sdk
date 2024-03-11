platform(osi-c1p COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_object_file(osi-c1p-crt0-o crt0.o crt0.s)

add_platform_library(osi-c1p-crt0)
merge_libraries(osi-c1p-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(osi-c1p-c
  abort.c
  putchar.cc
  getchar.c
  kbhit.s
)
target_include_directories(osi-c1p-c SYSTEM BEFORE PUBLIC .)
