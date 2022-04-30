cmake_minimum_required(VERSION 3.18)

project(examples LANGUAGES C CXX)

# Install examples to root example dir, not bin/
set(CMAKE_INSTALL_BINDIR .)

function(install_example target)
  install(TARGETS ${target})
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf TYPE BIN)
endfunction()

add_executable(minimal minimal.c)
install_example(minimal)
if(HOSTED)
  add_executable(hello-getchar hello-getchar.c)
  install_example(hello-getchar)
  add_executable(hello-malloc hello-malloc.c)
  install_example(hello-malloc)
  add_executable(hello-new hello-new.cc)
  install_example(hello-new)
  add_executable(hello-printf hello-printf.c)
  install_example(hello-printf)
  add_executable(hello-putchar hello-putchar.c)
  install_example(hello-putchar)
  add_executable(init-functions init-functions.cc)
  install_example(init-functions)
endif()

if(PLATFORM MATCHES ^nes-)
  add_subdirectory(nes)
endif()
