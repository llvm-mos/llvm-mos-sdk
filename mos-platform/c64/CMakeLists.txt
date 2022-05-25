platform(c64 COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES chrout.h TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_object_file(c64-basic-header basic-header.o basic-header.S)

add_platform_library(c64-crt0)
merge_libraries(c64-crt0
  common-init-stack
  common-zero-bss
  common-exit-return
)
target_compile_options(c64-crt0 PRIVATE -fno-lto)

add_platform_library(c64-c
  abort.c
  chrout.c
  putchar.c
  getchar.c
  kernal.S
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto)
target_include_directories(c64-c SYSTEM BEFORE PUBLIC .)
