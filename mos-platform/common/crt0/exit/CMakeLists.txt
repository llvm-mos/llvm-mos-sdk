# Exit by returning from _start.
add_platform_library(common-exit-return
  _exit.S
  exit-return.c
  exit.c
)
target_compile_options(common-exit-return PRIVATE -fno-lto)
target_include_directories(common-exit-return SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})

# Exit by calling a platform-provided _exit.
add_platform_library(common-exit-custom
  exit-custom.S
  exit.c
)
target_compile_options(common-exit-custom PRIVATE -fno-lto)
target_include_directories(common-exit-custom SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})

# Exit by entering an infinite loop.
add_platform_library(common-exit-loop
  exit-custom.S
  exit-loop.c
  exit.c
)
target_include_directories(common-exit-loop SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})
