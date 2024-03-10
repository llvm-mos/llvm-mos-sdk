platform(supervision COMPLETE PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES
  supervision.h
TYPE INCLUDE)

add_platform_object_file(supervision-crt0-o crt0.o crt0.c)

add_platform_library(supervision-crt0)
merge_libraries(supervision-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_platform_library(supervision-c
  supervision.c
  supervision.s
)
target_include_directories(supervision-c SYSTEM BEFORE PUBLIC .)
target_link_libraries(supervision-c PRIVATE common-asminc)
