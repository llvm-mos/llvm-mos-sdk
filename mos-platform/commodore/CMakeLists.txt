platform(commodore COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES chrout.h TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_object_file(commodore-basic-header basic-header.o basic-header.S)

add_platform_library(commodore-crt0)
merge_libraries(commodore-crt0
  common-init-stack
  common-zero-bss
  common-exit-return
)
target_compile_options(commodore-crt0 PRIVATE -fno-lto)

add_platform_library(commodore-c
  abort.c
  chrout.c
  putchar.c
  getchar.c
  kernal.S
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto)
target_include_directories(commodore-c SYSTEM BEFORE PUBLIC .)
