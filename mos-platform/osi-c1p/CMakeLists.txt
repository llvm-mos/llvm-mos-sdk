platform(osi-c1p COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_library(osi-c1p-crt0)
merge_libraries(osi-c1p-crt0
  common-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)
target_compile_options(osi-c1p-crt0 PRIVATE -fno-lto)

add_platform_library(osi-c1p-c
  abort.c
  putchar.cc
  getchar.c
)
merge_libraries(osi-c1p-c common-c)
target_include_directories(osi-c1p-c SYSTEM BEFORE PUBLIC .)

# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE abort.c PROPERTY COMPILE_FLAGS -fno-lto)
