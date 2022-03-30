platform(sim PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  add_platform_examples(sim-examples HOSTED)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES assert.h stdlib.h TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(sim-crt0)
merge_libraries(sim-crt0
  common-crt0
  common-exit-custom
  common-init-stack
)
target_compile_options(sim-crt0 PRIVATE -fno-lto)

add_platform_library(sim-c
  assert.c
  putchar.c
  stdlib.c
  sim-io.c
)
merge_libraries(sim-c common-c)
target_include_directories(sim-c SYSTEM BEFORE PUBLIC .)
