platform(nes-slrom COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_object_file(nes-slrom-crt0-o crt0.o ines.s)
