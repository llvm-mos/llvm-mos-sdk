platform(kim1-common HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES kim1.h TYPE INCLUDE)

add_platform_library(kim1-common-crt0)
merge_libraries(kim1-common-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(kim1-common-c
  monitor.s
  putchar.c
  getchar.c
)
target_include_directories(kim1-common-c SYSTEM BEFORE PUBLIC .)
