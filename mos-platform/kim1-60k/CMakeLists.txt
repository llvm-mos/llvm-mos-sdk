platform(kim1-60k COMPLETE HOSTED PARENT kim1-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_library(kim1-60k-crt0)
add_platform_library(kim1-60k-c)
