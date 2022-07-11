platform(commodore PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES chrout.h TYPE INCLUDE)
install(FILES commodore.ld TYPE LIB)

add_platform_library(commodore-crt0)
merge_libraries(commodore-crt0
  common-init-stack
  common-zero-bss
  common-exit-return
)

add_platform_library(commodore-c
  abort.c
  chrout.c
  putchar.c
  getchar.c
  kernal.S
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily. It can also be called in an interrupt.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto -fno-static-stack)
target_include_directories(commodore-c SYSTEM BEFORE PUBLIC .)
