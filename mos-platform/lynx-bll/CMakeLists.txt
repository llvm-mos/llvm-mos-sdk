platform(lynx-bll COMPLETE PARENT lynx)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  link.ld
TYPE LIB)
