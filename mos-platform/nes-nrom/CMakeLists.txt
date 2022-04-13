platform(nes-nrom PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES nes-nrom.ld TYPE LIB)

add_platform_object_file(nes-nrom-crt0-o crt0.o ines.s)
merge_libraries(nes-nrom-crt0-o nes-crt0-o)
