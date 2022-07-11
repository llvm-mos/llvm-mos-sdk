# crt0.o is the minimal startup functionality that must be included in any C
# binary. Anything that could be provided more than one wah should be in the
# derived platform's libcrt0.
add_platform_object_file(common-crt0-o crt0.o crt0.S)

# libcrt0 is a collection of initialization and finalization routines that may
# or may not be needed by a given program.
add_platform_library(common-crt0
  init-array.c
  fini-array.c
)
target_compile_options(common-crt0 PRIVATE -fno-lto)

# Zero out the BSS segment.
add_platform_library(common-zero-bss
  zero-bss.c
  zero-zp-bss.c
  )
target_compile_options(common-zero-bss PRIVATE -fno-lto)
target_include_directories(common-zero-bss SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})

# Copy the data segment from its load address (LMA) to it's runtime address
# (VMA).
add_platform_library(common-copy-data
  copy-data.c
  copy-zp-data.c
  )
target_compile_options(common-copy-data PRIVATE -fno-lto)
target_include_directories(common-copy-data SYSTEM BEFORE PUBLIC ${INCLUDE_DIR})

# Initialize the soft stack pointer to __stack.
add_platform_library(common-init-stack init-stack.S)

add_subdirectory(exit)
