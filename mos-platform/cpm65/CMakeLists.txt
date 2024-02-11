# © 2022 David Given
# This file is part of the llvm-mos-sdk project and is redistributable under the
# terms of the Apache 2.0 license with the LLVM exceptions. See the LICENSE file
# in the project root for the full text.

platform(cpm65 HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cpm.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(cpm65-crt0)
merge_libraries(cpm65-crt0
  common-init-stack
  common-copy-zp-data
  common-zero-bss
)

add_platform_library(cpm65-c
  cpm.S
  cpm-wrappers.c
  bios.S
  pblock.S
  putchar.c
  stack.S
  registers.S
)

target_include_directories(cpm65-c PUBLIC .)
