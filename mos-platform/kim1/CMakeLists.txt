platform(kim1 COMPLETE HOSTED PARENT kim1-common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_library(kim1-crt0)
add_platform_library(kim1-c)
